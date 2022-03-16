# Big Integer Library

## Introduction
This repository is a C implementation of a software-based Big Unsigned Integer Library. The specific interface can be found below. Numbers are represented as pointers to 32-bit unsigned integers. We use a base of 2^32 for each digit. Below is an example of such a number in C
``` uint32_t x[] = { 0x12345678, 0x12345678 } = 1,311,768,465,173,141,112 ```

## Implementation
The following contains a list of all the Big Integer methods included.
<ol>
    <li>big_uint_equals</li>
    <li>big_uint_cmp</li>
    <li>big_uint_max</li>
    <li>big_uint_min</li>
    <li>big_uint_cpy</li>
    <li>big_uint_swap</li>
    <li>big_uint_sprint</li>
    <li>big_uint_print</li>
    <li>big_uint_shl</li>
    <li>big_uint_shl2</li>
    <li>big_uint_shr</li>
    <li>big_uint_shr2</li>
    <li>big_uint_or</li>
    <li>big_uint_and</li>
    <li>big_uint_xor</li>
    <li>big_uint_add</li>
    <li>big_uint_sub</li>
    <li>big_uint_mult</li>
    <li>big_uint_div</li>
    <li>big_uint_gcd</li>
    <li>big_uint_gcd_extended</li>
</ol>