package com.frank.myndkmodule

import android.Manifest
import android.content.Intent
import android.os.Bundle
import android.os.Environment
import android.util.Log
import android.widget.Toast
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.act_test.*
import permissions.dispatcher.NeedsPermission
import permissions.dispatcher.RuntimePermissions
import java.io.File

@RuntimePermissions
class TestAct : AppCompatActivity() {


    companion object {
        const val TAG = "应用层"
        val name = "clark"

        init {
            System.loadLibrary("jni-lib")
        }

        @JvmStatic
        fun sayHello() {
            Log.e(TAG, "invoke from c")
        }

        fun sayHello(name: String) {
            Log.e(TAG, "hello,$name")
        }

    }

    fun printAddress(): String {
        Log.e(TAG, "hello,$address")
        return address
    }


    val address = "株洲"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.act_test)
        tv.text = stringFromJNI()
        //readSDCardWithPermissionCheck()
        val newArray = processIntArray(intArrayOf(0, 1, 2, 3, 4))
        for (i in newArray) {
            Log.e(TAG, "$i")
        }
        invokeKotlinStaticMethod()
        Log.e(TAG, "$name")
        invokeKotlinMethod("nick")
    }

    @NeedsPermission(
        Manifest.permission.WRITE_EXTERNAL_STORAGE,
        Manifest.permission.READ_EXTERNAL_STORAGE
    )
    fun readSDCard() {
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

    external fun processIntArray(array: IntArray): IntArray

    external fun invokeKotlinStaticMethod()

    external fun invokeKotlinMethod(add: String)
}