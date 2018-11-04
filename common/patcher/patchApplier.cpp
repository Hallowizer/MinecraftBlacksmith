//
//  patchApplier.cpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/3/18.
//
//

#include <stdlib.h>
#include <iostream>

#include "patchApplier.hpp"

struct patchInstruction;

struct patch {
    char magic1;
    char magic2;
    char magic3;
    char magic4;
    
    struct patchInstruction instructions[];
};

struct patchInstruction {
    int code;
    
    union {
        struct {
            unsigned short length;
            char value[];
        } dataUshort;
        
        struct {
            int length;
            char value[];
        } dataInt;
        
        struct {
            unsigned short offset;
            unsigned char length;
        } copyUshortUbyte;
        
        struct {
            unsigned short offset;
            unsigned short length;
        } copyUshortUshort;
        
        struct {
            unsigned short offset;
            int length;
        } copyUshortInt;
        
        struct {
            int offset;
            unsigned char length;
        } copyIntUbyte;
        
        struct {
            int offset;
            unsigned short length;
        } copyIntUshort;
        
        struct {
            int offset;
            int length;
        } copyIntInt;
        
        struct {
            long offset;
            int length;
        } copyLongInt;
    } data;
};

char *patch(char *source, FILE *patchSource, int patchLength) {
    struct patch *data = (struct patch *) malloc(patchLength);
    fread(data, patchLength, 1, patchSource);
    
    if (data->magic1 != 0x93 || data->magic2 != 0x37 || data->magic3 != 0x8d || data->magic4 != 0x01) {
        cerr << "Invalid patch format.";
        return source;
    }
    
    int offset = 0;
    
    char *output = (char *) malloc(CHUNK_SIZE);
    int len = CHUNK_SIZE;
    int used = 0;
    
    int i;
    for (i = 0; !done; i++) {
        patchInstruction insn = data->instructions[i];
        
        if (insn->code == EOF)
            break;
        
        if (insn->code <= DATA_MAX) {
            write(&output, &len, &used, &(insn->code));
            continue;
        }
        
        switch (insn->code) {
            case DATA_USHORT:
                append(&output, &len, &used, insn->data.dataUshort.length, insn->data.dataUshort.value);
                break;
            case DATA_INT:
                append(&output, &len, &used, insn->data.dataInt.length, insn->dataInt.value);
                break;
            case COPY_USHORT_UBYTE:
                copy(&offset, source, &output, &len, &used, insn->data.copyUshortUbyte.offset, insn->data.copyUshortUbyte.length);
                break;
            case COPY_USHORT_USHORT:
                copy(&offset, source, &output, &len, &used, insn->data.copyUshortUshort.offset, insn->data.copyUshortUshort.length);
                breakl
            case COPY_USHORT_INT:
                copy(&offset, source, &output, &len, &used, insn->data.copyUshortInt.offset, insn->data.copyUshortInt.length);
                break;
            case COPY_INT_UBYTE:
                copy(&offset, source, &output, &len, &used, insn->data.copyIntUbyte.offset, insn->data.copyIntUbyte.length);
                break;
            case COPY_INT_USHORT:
                copy(&offset, source, &output, &len, &used, insn->data.copyIntUshort.offset, insn->data.copyIntUshort.length);
                break;
            case COPY_INT_INT:
                copy(&offset, source, &output, &len, &used, insn->data.copyIntInt.offset, insn->data.copyIntInt.length);
                break;
            case COPY_LONG_INT:
                copy(&offset, source, &output, &len, &used, insn->data.copyLongInt.offset, insn->data.copyLongInt.length);
                break;
        }
    }
    
    return (char *) realloc(output, used);
}

static void append(char **output, int *len, int *used, int length, char *value) {
    write(output, len, used, length, value);
}

static void copy(int *readOffset, const char *input, char **output, int *len, int *used, long offset, int length) {
    free(read(readOffset, input, offset)); // Skip the offset bytes.
    
    char *toCopy = read(readOffset, input, length);
    write(output, len, used, length, toCopy);
    free(toCopy);
}

static char *read(int *readOffset, const char *input, long length) {
    char *data = (char *) malloc(length);
    
    long i;
    for (i = 0; i < length; i++)
        data[i] = input[i+(*readOffset)];
    
    (*readOffset) += length;
    return data;
}

static void write(char **output, int *len, int *used, int length, const char *data) {
    if (used+length > len) {
        (*len) += CHUNK_SIZE;
        (*output) = (char *) realloc(*output, *len);
    }
    
    int i;
    for (i = 0; i < length; i++)
        output[i+(*used)] = data[i];
    
    (*used) += length;
}
