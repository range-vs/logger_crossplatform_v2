package com.test.logger.android;

import android.app.Application;
import android.util.Log;

public class App extends Application
{
    protected static App app = null;

    public static App getApp()
    {
        return app;
    }

    @Override public void onCreate()
    {
        app = this;
        super.onCreate();

    }
}
