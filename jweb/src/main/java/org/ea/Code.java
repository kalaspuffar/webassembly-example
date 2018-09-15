package org.ea;

import de.inetsoftware.jwebassembly.api.annotation.Export;

public class Code {
    @Export
    public static int add( int a, int b ) {
        return a + b + 4;
    }
}