package com.bob.ctf;

public class CodeCheck {
    private native String keyme(String name);

    public boolean check_code(String arg1) {
        keyme(arg1);
        return true;
    }
}
