//
//  patchApplier.cpp
//  MinecraftBlacksmith
//
//  Created by Hallowizer on 11/3/18.
//
//

#include <stdlib.h>
#include <iostream>

using namespace std;

#include "patchApplier.hpp"
#include "patchConstants.hpp"

static void append(char **, int *, int *, int, FILE *);
static void copy(int *, const char *, char **, int *, int *, long, int);

static void skip(int *, const char *, long);
static char *read(int *, const char *, long);
static void write(char **, int *, int *, int, char *);

struct patchMagic {
	char magic1;
	char magic2;
	char magic3;
	char magic4;
};

struct patchInstruction {
	int code;
	
	union {
		// Data instructions. All data instruction fields are length fields. Byte contents are after length field.
		unsigned short dataUshort;
		int dataInt;
		
		// Copy instructions. These vary in size.
		
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
	struct patchMagic *magic = (struct patchMagic *) malloc(sizeof(struct patchMagic));
	fread(magic, sizeof(struct patchMagic), 1, patchSource);
	
	if (magic->magic1 != 0x93 || magic->magic2 != 0x37 || magic->magic3 != 0x8d || magic->magic4 != 0x01) {
		cerr << "Invalid patch format.";
		return source;
	}
	
	free(magic);
	
	int offset = 0;
	
	char *output = (char *) malloc(CHUNK_SIZE);
	int len = CHUNK_SIZE;
	int used = 0;
	
	int i;
	for (i = 0; ; i++) {
		struct patchInstruction *insn = malloc(sizeof(struct patchInstruction));
		fread(insn, sizeof(struct patchInstruction), 1, patchSource);
		
		if (insn->code == EOF) {
			free(insn);
			break;
		}
		
		if (insn->code <= DATA_MAX) {
			write(&output, &len, &used, 1, (char *) &(insn->code));
			
			free(insn);
			continue;
		}
		
		switch (insn->code) {
		case DATA_USHORT:
			append(&output, &len, &used, insn->data.dataUshort, patchSource);
			break;
		case DATA_INT:
			append(&output, &len, &used, insn->data.dataInt, patchSource);
			break;
		case COPY_USHORT_UBYTE:
			copy(&offset, source, &output, &len, &used, insn->data.copyUshortUbyte.offset, insn->data.copyUshortUbyte.length);
			break;
		case COPY_USHORT_USHORT:
			copy(&offset, source, &output, &len, &used, insn->data.copyUshortUshort.offset, insn->data.copyUshortUshort.length);
			break;
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
		
		free(insn);
	}
	
	free(source);
	return (char *) realloc(output, used);
}

static void append(char **output, int *len, int *used, int length, FILE *src) {
	char *data = malloc(length);
	fread(data, 1, length, src);
	
	write(output, len, used, length, data);
	
	free(data);
}

static void copy(int *readOffset, const char *input, char **output, int *len, int *used, long offset, int length) {
	skip(readOffset, input, offset);
	
	char *toCopy = read(readOffset, input, length);
	write(output, len, used, length, toCopy);
	free(toCopy);
}

static void skip(int *readOffset, const char *input, long length) {
	char *ptr = read(readOffset, input, length);
	free(ptr);
}

static char *read(int *readOffset, const char *input, long length) {
	char *data = (char *) malloc(length);
	
	long i;
	for (i = 0; i < length; i++)
		data[i] = input[i+(*readOffset)];
	
	(*readOffset) += length;
	return data;
}

static void write(char **output, int *len, int *used, int length, char *value) {
	if (used+length > &len) {
		(*len) += CHUNK_SIZE;
		(*output) = (char *) realloc(*output, *len);
	}
	
	int i;
	for (i = 0; i < length; i++)
		output[i+(*used)] = value[i];
	
	(*used) += length;
}
