package com.frank.lamelibrary

class MP3Encoder {


    companion object {
        external fun getLameVersion(): String
        external fun init(pcmPath: String, mp3Path: String): Int
        //external fun encode()
        //external fun destroy()
    }
}