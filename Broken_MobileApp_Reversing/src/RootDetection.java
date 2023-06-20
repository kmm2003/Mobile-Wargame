package com.bob.ctf;

import android.os.Build;

import java.io.File;

public class RootDetection {
    public static boolean checkRoot1() {
        String[] paths = System.getenv("PATH").split(":");
        for (int i = 0; i < paths.length; i++) {
            if (new File(paths[i], "su").exists()) {
                return true;
            }
        }
        return false;
    }

    public static boolean checkRoot2() {
        boolean isTestKeys = Build.TAGS != null && Build.TAGS.contains("test-keys");
        return isTestKeys;
    }

    public static boolean checkRoot3() {
        String[] files = new String[]{
                "/system/app/Superuser.apk",
                "/system/xbin/daemonsu",
                "/system/etc/init.d/99SuperSUDaemon",
                "/system/bin/.ext/.su",
                "/system/etc/.has_su_daemon",
                "/system/etc/.installed_su_daemon",
                "/dev/com.koushikdutta.superuser.daemon/"
        };
        for (int i = 0; i < files.length; i++) {
            if (new File(files[i]).exists()) {
                return true;
            }
        }
        return false;
    }
}

