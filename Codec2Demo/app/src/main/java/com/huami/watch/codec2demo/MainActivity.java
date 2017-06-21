package com.huami.watch.codec2demo;

import android.content.res.AssetManager;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.widget.TextView;

import com.huami.watch.codec2.Codec2;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

public class MainActivity extends AppCompatActivity {

    private static final String TAG = "MainActivity";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

    // Example of a call to a native method
    TextView tv = (TextView) findViewById(R.id.sample_text);
        Codec2.initCodec2(Codec2.CODEC2_MODE_1300);
        int n = Codec2.getDecodeDataLen();
        int k = Codec2.getEncodeDataLen();

        InputStream inputStream = getResources().openRawResource(R.raw.hts1a);

        FileOutputStream outputStream;
        File file = new File("/sdcard/hts.bit");
        if(!file.exists()) {
            try {
                file.createNewFile();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        try {
            outputStream = new FileOutputStream(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            Log.w(TAG,"new FileOutputStream failed!");
            return;
        }
        byte[] buf = new byte[k*2];
        byte[] encodedBits;
        try {
            while(inputStream.read(buf,0,k*2)>0) {
                short[] encodeData =
                        MemoryUtils.toShortArray(buf,0,k*2);
                encodedBits = Codec2.codec2Encode(encodeData,k);
                if(encodedBits!=null) {
                    Log.d(TAG, "encode result lenght:" + encodedBits.length);
                } else {
                    Log.w(TAG, "encode result is null!!!");
                }
                outputStream.write(encodedBits);
            }
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            try {
                inputStream.close();
                outputStream.close();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
//        Codec2.codec2Decode(new byte[n],n);
        Codec2.codec2Destroy();
    }
}
