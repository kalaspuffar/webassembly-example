package org.ea;

import de.inetsoftware.jwebassembly.JWebAssembly;

import java.io.File;
import java.net.URL;

public class JWebExample {
    public static void main(String[] args) {
        File wasmFile = new File( "test.wasm" );
        JWebAssembly wasm = new JWebAssembly();

        Class clazz = Code.class;

        URL url = clazz.getResource(
                '/' +
                clazz.getName().replace( '.', '/' ) +
                        ".class" );
        wasm.addFile( url );
        wasm.compileToBinary( wasmFile );
    }
}