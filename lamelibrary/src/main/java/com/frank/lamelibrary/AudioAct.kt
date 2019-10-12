package com.frank.lamelibrary

import android.Manifest
import android.os.Bundle
import android.os.Environment
import androidx.appcompat.app.AppCompatActivity
import kotlinx.android.synthetic.main.act_audio.*
import permissions.dispatcher.NeedsPermission
import permissions.dispatcher.RuntimePermissions
import java.io.File

@RuntimePermissions
class AudioAct : AppCompatActivity() {

    companion object {
        init {
            System.loadLibrary("audio-lib");
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.act_audio)
        tvVersion.text = MP3Encoder.getLameVersion()
        encodePCMFileWithPermissionCheck()
    }


    @NeedsPermission(
        Manifest.permission.WRITE_EXTERNAL_STORAGE,
        Manifest.permission.READ_EXTERNAL_STORAGE
    )
    fun encodePCMFile() {
        val pcmPath =
            Environment.getExternalStorageDirectory().toString() + File.separator + "boys.pcm"
        val mp3Path =
            Environment.getExternalStorageDirectory().toString() + File.separator + "boys.mp3"
        MP3Encoder.init(pcmPath, mp3Path)
    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        onRequestPermissionsResult(requestCode, grantResults)
    }
}