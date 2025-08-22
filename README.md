# Quine — a self-replicating (self-referential) program that outputs its own source code.

https://en.wikipedia.org/wiki/Quine_(computing)

A quine is a computer program that takes no input and produces a copy of its own source code as its only output. 

in C, Quine works because printf is printing a string that includes itself, with the values inserted in the right places instead of placeholders.

printf() is a formatted output function. It takes a format string, which may contain placeholders like %s, %c, %d, etc., and a list of arguments that replace those placeholders.

The recursion is handled not by the function calling itself, but by printing a string that looks exactly like the original source code.

## Self-replication Logic

The string to print contains a placeholder for itself — printf() is used to plug itself into itself.
It’s self-referential: the string contains a %s, and the %s gets replaced with the string itself.

In a quine the string to print is the template/blueprint of the program — not the payload.


### Encountered Errors:
If the format string has more % placeholders than there are supplying arguments for, or there's an extra % not forming a valid placeholder (like %c, %s, etc.) or there's a rogue % not followed by a valid format character, it prints %.

Placeholder %c, the ASCII injected values and purpose

 034	042	22	0010 0010	"	double quote
 035	043	23	0010 0011	#	number sign
 037	045	25	0010 0101	%	percent
 47     057	2F	00101111	/   Slash or divide
 059	073	3B	0011 1011	;	semi-colon
 092	134	5C	0101 1100	\	back slash
 110	156	6E	0110 1110	n
 010	012	0A	0000 1010	LF	line feed \n
 

## Test01

 #include <stdio.h>
 int main(){
 char* command = "print something\n";
 printf("%s",command);
 return 0;
 }

print something

## Test02

 #include <stdio.h>
 int main(){
 char* command = "print something %s";
 printf(command, command);
 return 0;
 }

print something print something %s%

## Test03

 #include <stdio.h>
 int main(){
 char* command = "#include <stdio.h>\nint main(){\nchar* command = command %s;\nprintf(command, command);\nreturn 0;\n}";
 printf(command, command);
 return 0;
 }

 include <stdio.h>
 int main(){
 char* command = command #include <stdio.h>
 int main(){
 char* command = command %s;
 printf(command, command);
 return 0;
 };
 printf(command, command);
 return 0;
 }%

## Test04

 #include <stdio.h>
 int main(){
 char* command = "#include <stdio.h>%c%cchar* command = command %s;}";
 printf(command, 92,110, command);
 return 0;
 }

#include <stdio.h>\nchar* command = command #include <stdio.h>%c%cchar* command = command %s;};}%

## Test05

 #include <stdio.h>
 int main(){
 char* command = "#include <stdio.h>%cchar* command = command %s;}";
 printf(command, 10, command);
 return 0;
 }

#include <stdio.h>
char* command = command #include <stdio.h>%cchar* command = command %s;};}%

## Test06

 #include <stdio.h>
 int main(){
 char* command = "#include <stdio.h>%cchar* command = command %s;%c}";
 printf(command, 10, command, 10);
 return 0;
 }

#include <stdio.h>
char* command = command #include <stdio.h>%cchar* command = command %s;%c};
}%

## Test07

 #include <stdio.h>
 int main(){
 char* command = "#include <stdio.h>%cchar* command = command %s;%cprintf(command, 10, command, 10);%creturn 0;%c}";
 printf(command, 10, command, 10, 10, 10);
 return 0;
 }

 #include <stdio.h>
 char* command = command #include <stdio.h>%cchar* command = command %s;%cprintf(command, 10, command, 10);%creturn 0;%c};
 printf(command, 10, command, 10);
 return 0;
 }%

## Test08

 #include <stdio.h>
 int main(){
 char* command = "#include <stdio.h>%cint main(){%cchar* command1 = command %s;%cprintf(command, 10, command, 10);%creturn 0;%c}%c";
 printf(command, 10, 10, command, 10, 10, 10, 10);
 return 0;
 }

 #include <stdio.h>
 int main(){
 char* command1 = command #include <stdio.h>%cint main(){%cchar* command1 = command %s;%cprintf(command, 10, command, 10);%creturn 0;%c}%c;
 printf(command, 10, command, 10);
 return 0;
 }

## Test09

 #include <stdio.h>
 int main(){
 char* command = "print something %c%s%c%c";
 printf(command, 34,command,34,10);
 return 0;
 }

 print something "print something %c%s%c%c"

## FINAL

#include <stdio.h>
int main(){
char* command = "#include <stdio.h>%cint main(){%cchar* command = %c%s%c;%cprintf(command, 10, 10, 34, command, 34, 10, 10, 10);%creturn 0;%c}%c";
printf(command, 10, 10, 34, command, 34, 10, 10, 10);
return 0;
}

## Possible final

#include <stdio.h>

int main() {
    char *source = "#include <stdio.h>%c%cint main() {%c%cchar *quine = %c%s%c;%c%cprintf(quine, 10, 10, 10, 34, quine, 34, 10, 10, 10);%c%creturn 0;%c}%c";
    printf(source, 10, 10, 10, 9, 34, source, 34, 10, 9, 10, 9, 10, 10);
    return 0;
}

Yes — absolutely. You **can split `char *quine` into multiple parts**, and it’s actually a smart move for readability and maintainability.

Quines are notorious for long, hard-to-read format strings, so breaking the source into **two or more strings** (and stitching them together in your logic) is completely valid — *as long as the final output is identical to the original source code*.

---

## ✅ Why Splitting Makes Sense

* It keeps each string readable.
* It avoids deeply nested escape sequences.
* You can separate **static text** (the structure) from **dynamic content** (like the string itself).
* It makes debugging your `%c` and `%s` placeholders much easier.

---

## 🧠 Common Approaches to Splitting

### ✅ 1. **Separate format structure and actual content**

```c
char *part1 = "...";
char *part2 = "...";
```

Then in `printf()`:

```c
printf(part1, ..., part2, ...);
```

You might even do:

* `part1` for the top half of the file
* `part2` for the `main()` logic
* Or something like:

  * `prefix`: before the format string
  * `middle`: the format string declaration
  * `suffix`: rest of the file

You can then build your output across **multiple `printf()` calls**.

---

### ✅ 2. **Store parts in an array of strings**

This lets you loop through and print the source line-by-line if needed:

```c
char *lines[] = {
    "#include <stdio.h>",
    "void print_source() {",
    // ...
};
```

Then iterate:

```c
for (int i = 0; i < N; i++)
    printf("%s\n", lines[i]);
```

⚠️ This adds complexity (and won't work easily with the self-replicating format string style), but it’s still a valid conceptual approach depending on how you're building your quine.

---

### ✅ 3. **Use string concatenation carefully**

In C, you can concatenate adjacent string literals:

```c
char *quine =
    "#include <stdio.h>\n"
    "void print_source(char *q) {\n"
    "    printf(q, q);\n"
    "}\n";
```

This doesn’t change the string — the compiler joins them together — but it **makes the source more readable** and lets you structure it logically.

---

## ⚠️ Just Remember

* However you split the source, your program must **reproduce the complete file** exactly.
* The actual source code (`.c` file) must match the output **byte for byte**.
* So, even if you split the string into two or more parts, you’ll still need to **pass both** (or combine them logically) into the output stream correctly.

---

## ✅ TL;DR

* **Yes**, you can split `char *quine` into multiple parts.
* Just make sure your program **still outputs the full, exact source code**.
* You can:

  * Use multiple `char *` strings
  * Join strings with adjacent literals
  * Print them in parts via `printf()`
* Doing this can make your quine **easier to debug and read**, which is a huge benefit.

---

## 🔍 What does this mean?

In **C**, when you write **two or more string literals next to each other**, they are **automatically concatenated at compile time**.

---

### ✅ Example:

```c
char *s = "Hello, "
          "world!";
```

This is **equivalent to**:

```c
char *s = "Hello, world!";
```

You don’t need to use `strcat()` or manually join them. The compiler combines them into one single string.

---

### 🧠 Why is this useful?

It helps **break up long strings** across multiple lines for readability — especially when you’re working with:

* Long format strings (like in a quine)
* Code-generation logic
* Escape-heavy text

---

### ✅ Quine Example Use

In the context of a quine, you might have a long `char *quine` like:

```c
char *quine = "#include <stdio.h>\nvoid main() {\n   // code\n}";
```

This is hard to read and maintain. So you can split it up:

```c
char *quine =
    "#include <stdio.h>\n"
    "void main() {\n"
    "    // code\n"
    "}\n";
```

The compiler will treat this as **one continuous string**:

```
"#include <stdio.h>\nvoid main() {\n    // code\n}\n"
```

You get **the same result**, but it’s now readable and easier to debug.

---

## ⚠️ Important Notes

* This only works with **string literals**, not with variables.
* You can use as many adjacent literals as you want.
* This doesn’t insert any space or newline between them — you control that explicitly (via `\n`, ` `, etc).

---

## Summary

| Feature                  | Result                        |
| ------------------------ | ----------------------------- |
| Adjacent string literals | Automatically joined          |
| Helps with               | Readability, formatting       |
| Used for                 | Long strings (like in quines) |

---

## ✳️ TL;DR:

```c
char *s = "Hello, "
          "world!";
```

Is **the same as**:

```c
char *s = "Hello, world!";
```
