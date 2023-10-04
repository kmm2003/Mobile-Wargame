package com.dreamhack.reversing;

import androidx.appcompat.app.AppCompatActivity;

import android.os.AsyncTask;
import android.os.Bundle;
import android.os.Debug;
import android.os.SystemClock;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.app.AlertDialog;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "happy_hacking!";
    private CodeCheck check;
    static int tampered = 0;
    // DH{a4bab3ce420ea5342f99b468}
    private static final String key =  "[Wd~+}~},|z+-/z~*,+-y&&}+)'b";

    // Used to load the 'ctf' library on application startup.
    static {
        System.loadLibrary("reversing");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        new AsyncTask<Void, Void, String>() {
            @Override
            protected String doInBackground(Void... arg3) {
                while (!Debug.isDebuggerConnected()) {
                    SystemClock.sleep(100L);
                }
                return null;
            }

            @Override
            protected void onPostExecute(String arg2) {
                MainActivity.this.showDialog("Debugger detected!");
                System.exit(0);
            }
        }.execute();
        if (RootDetection.checkRoot1() || RootDetection.checkRoot2() || RootDetection.checkRoot3() || IntegrityCheck.isDebuggable(this.getApplicationContext()) || MainActivity.tampered != 0) {
            this.showDialog("Rooting or tampering detected.");
        }

        this.check = new CodeCheck();
        super.onCreate(savedInstanceState);
        this.setContentView(R.layout.activity_main);
        Button btn = findViewById(R.id.btn);

        btn.setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                verify();
            }
        });
    }

    private void showDialog(String arg4) {
        AlertDialog v0 = new AlertDialog.Builder(this).create();
        v0.setTitle(arg4);
        v0.setMessage("No! This is hacked.");
        v0.setButton(AlertDialog.BUTTON_NEGATIVE, "OK", (dialog, which) -> System.exit(0));
        v0.setCancelable(false);
        v0.show();
    }

    public void verify() {
        String v4 = ((EditText)findViewById(R.id.edit_text)).getText().toString();
        AlertDialog v0 = new AlertDialog.Builder(this).create();
        if(check.check_code(key)) {
            v0.setTitle("Good!");
            v0.setMessage("DH{this_i$_r5al_fl@g?}");
        } else {
            v0.setTitle("Nope...");
            v0.setMessage("That's not it. Try again.");
        }
        v0.setButton(AlertDialog.BUTTON_NEGATIVE, "OK", (dialog, which) -> dialog.dismiss());
        v0.show();
    }
}