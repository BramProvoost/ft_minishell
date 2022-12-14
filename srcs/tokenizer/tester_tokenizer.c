// #include "../main.h"
// #include <criterion/criterion.h>
// #include <criterion/criterion.h>
#include "../../Criterion/include/criterion/criterion.h"
// #include "/Users/bprovoos/homebrew/opt/criterion/include/criterion/criterion.h"

Test(misc, failing) {
	cr_assert(0);
}

Test(misc, passing) {
	cr_assert(1);
}

// Test(asserts, tokenizer_tester)
// {
// 	cr_assert(1);
// 	cr_assert(eq(str, "hello", "hello"));
// }

// Test(asserts, base)
// {
// 	cr_assert(true);
// 	cr_expect(true);

// 	cr_assert(true, "Assertions may take failure messages");

// 	cr_assert(true, "Or even %d format string %s", 1, "with parameters");

// 	cr_expect(false, "assert is fatal, expect isn't");
// 	cr_assert(false, "This assert runs");
// 	cr_assert(false, "This does not");
// }

