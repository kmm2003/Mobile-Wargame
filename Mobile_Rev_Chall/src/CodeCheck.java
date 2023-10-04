package com.dreamhack.reversing;

public class CodeCheck {
    private native boolean chall(String name);

    public boolean check_code(String key) {
        chall(key);
        return true;
    }
}