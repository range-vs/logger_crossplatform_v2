package com.test.logger.android;

import androidx.appcompat.app.AppCompatActivity;
import androidx.core.app.ActivityCompat;
import androidx.core.content.ContextCompat;

import android.Manifest;
import android.app.Activity;
import android.content.ContextWrapper;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.widget.ActionMenuView;
import android.widget.TextView;
import android.widget.Toast;

import java.io.File;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = MainActivity.class.getSimpleName();

    static {
        System.loadLibrary("native-lib");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.sample_text);
        tv.setText("Test logger app");

        checkForStoragePermission();

    }

    public static String getLogsPath() throws Exception {
        String suffix = "/" + App.getApp().getPackageName() + "/logs/";
        String[] paths = {  Environment.getExternalStoragePublicDirectory(Environment.DIRECTORY_DOWNLOADS).getPath() + suffix,
                            App.getApp().getFilesDir().getPath() + "/logs/" };

        for( int i = 0; i < paths.length; ++i) {
            File f = new File(paths[i]);
            f.mkdirs();
            if( f.canWrite() && f.canRead()) {
                return paths[i];
            }
        }

        throw new Exception("getLogsPath() is unable to find appropriate logs directory. You should check permissions or something...");
    }

    void initLogger(){
        // init logger cpp
        try {
            initLogger(getLogsPath() + "log.html", this);
        } catch (Exception e) {
            Log.e(TAG, e.getMessage());
            e.printStackTrace();
        }
    }

    private static final int APPS_PERMISSIONS_EXTERNAL_STORAGE = 10000;

    private void checkForStoragePermission() {
        if (ActivityCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) != 0) {
            ActivityCompat.requestPermissions(this, new String[]{Manifest.permission.WRITE_EXTERNAL_STORAGE}, APPS_PERMISSIONS_EXTERNAL_STORAGE);
            return;
        }
    }

    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case APPS_PERMISSIONS_EXTERNAL_STORAGE: {
                if (permissions[0].equalsIgnoreCase(Manifest.permission.WRITE_EXTERNAL_STORAGE) && grantResults[0] == 0) {
                    initLogger();
                } else {
                    String msg = String.format("You must enable %s permission to enable logger", Manifest.permission.WRITE_EXTERNAL_STORAGE);
                    Log.d(TAG, msg);
                    Toast.makeText(getApplicationContext(), msg, Toast.LENGTH_LONG).show();
                }
                break;
            }
        }
        super.onRequestPermissionsResult(requestCode, permissions, grantResults);
    }

    public native void initLogger(String pathLog, Activity activity);
}