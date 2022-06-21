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
import android.widget.ActionMenuView;
import android.widget.TextView;
import android.widget.Toast;

public class MainActivity extends AppCompatActivity {

    static {
        System.loadLibrary("native-lib");
    }

    private static final int REQUEST_EXTERNAL_STORAGE = 1;
    private static String[] PERMISSIONS_STORAGE = {
            Manifest.permission.READ_EXTERNAL_STORAGE,
            Manifest.permission.WRITE_EXTERNAL_STORAGE,
            Manifest.permission.MANAGE_EXTERNAL_STORAGE
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        TextView tv = findViewById(R.id.sample_text);
        tv.setText("Test logger app");

        //Toast.makeText(null, "test", Toast.LENGTH_LONG).show();

        if (Build.VERSION.SDK_INT > Build.VERSION_CODES.M) {
            verifyStoragePermissions(this);
        }



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
        initLogger(getLogsPath() + "log.html", this);
    }

    public void verifyStoragePermissions(Activity activity) {
        // Check if we have write permission
        int permission = ActivityCompat.checkSelfPermission(activity, Manifest.permission.MANAGE_EXTERNAL_STORAGE);

        if (permission != PackageManager.PERMISSION_GRANTED) {
            // We don't have permission so prompt the user
            ActivityCompat.requestPermissions(
                    activity,
                    PERMISSIONS_STORAGE,
                    REQUEST_EXTERNAL_STORAGE
            );
        }else{
            initLogger();
        }
    }

    @Override
    public void onRequestPermissionsResult(int requestCode, String[] permissions, int[] grantResults) {
        switch (requestCode) {
            case 1:
                if (grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                    initLogger();
                    Toast.makeText(this, "Permission Granted" , Toast.LENGTH_LONG).show();
                } else {
                    //permission with request code 1 was not granted
                    Toast.makeText(this, "Permission was not Granted" , Toast.LENGTH_LONG).show();
                }
                break;
            default:
                super.onRequestPermissionsResult(requestCode, permissions, grantResults);
        }
    }

    public native void initLogger(String pathLog, Activity activity);
}