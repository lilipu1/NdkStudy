package com.frank.myndkmodule

import android.Manifest
import android.content.Intent
import android.os.Bundle
import android.os.Environment
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.act_test.*
import permissions.dispatcher.NeedsPermission
import permissions.dispatcher.RuntimePermissions
import java.io.File

@RuntimePermissions
class TestAct : AppCompatActivity() {

    companion object {
        init {
            System.loadLibrary("jni-lib")
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.act_test)
        tv.text = stringFromJNI()
        readSDCardWithPermissionCheck()
    }

    @NeedsPermission(
        Manifest.permission.WRITE_EXTERNAL_STORAGE,
        Manifest.permission.READ_EXTERNAL_STORAGE
    )
    fun readSDCard() {
        //Toast.makeText(this, "有权限", Toast.LENGTH_SHORT).show()
        processFile(Environment.getExternalStorageDirectory().toString() + File.separator + "boys.txt")
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        onRequestPermissionsResult(requestCode, grantResults)
    }

    external fun stringFromJNI(): String

    external fun processFile(filePath: String)

}