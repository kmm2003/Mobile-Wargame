package com.bob.ctf;

import android.content.Context;

public class IntegrityCheck {
    public static boolean isDebuggable(Context context) {
        boolean isDebuggable = (context.getApplicationContext().getApplicationInfo().flags & 2) != 0;
        return isDebuggable;
    }
}