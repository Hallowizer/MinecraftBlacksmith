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

static void append(vector<char>&, int, FILE *);
static void copy(vector<char>&, vector<char>&, int *, long, int);

static void skip(int *, vector<char>&, long);
static char *read(int *, vector<char>&, long);
static void write(vector<char>&, int, const char *);

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

void patch(vector<char>& bytes, FILE *patchSource) {
	struct patchMagic *magic = (struct patchMagic *) malloc(sizeof(struct patchMagic));
	fread(magic, sizeof(struct patchMagic), 1, patchSource);
	
	if (magic->magic1 != 0x93 || magic->magic2 != 0x37 || magic->magic3 != 0x8d || magic->magic4 != 0x01) {
		cerr << "Invalid patch format.";
		return;
	}
	
	free(magic);
	
	int readIndex = 0;
	vector<char> output;
	
	int i;
	for (i = 0; ; i++) {
		struct patchInstruction *insn = malloc(sizeof(struct patchInstruction));
		fread(insn, sizeof(struct patchInstruction), 1, patchSource);
		
		if (insn->code == EOF) {
			free(insn);
			break;
		}
		
		if (insn->code <= DATA_MAX) {
			write(output, 1, (char *) &(insn->code));
			
			free(insn);
			continue;
		}
		
		switch (insn->code) {
		case DATA_USHORT:
			append(output, insn->data.dataUshort, patchSource);
			break;
		case DATA_INT:
			append(output, insn->data.dataInt, patchSource);
			break;
		case COPY_USHORT_UBYTE:
			copy(bytes, output, &readIndex, insn->data.copyUshortUbyte.offset, insn->data.copyUshortUbyte.length);
			break;
		case COPY_USHORT_USHORT:
			copy(bytes, output, &readIndex, insn->data.copyUshortUshort.offset, insn->data.copyUshortUshort.length);
			break;
		case COPY_USHORT_INT:
			copy(bytes, output, &readIndex, insn->data.copyUshortInt.offset, insn->data.copyUshortInt.length);
			break;
		case COPY_INT_UBYTE:
			copy(bytes, output, &readIndex, insn->data.copyIntUbyte.offset, insn->data.copyIntUbyte.length);
			break;
		case COPY_INT_USHORT:
			copy(bytes, output, &readIndex, insn->data.copyIntUshort.offset, insn->data.copyIntUshort.length);
			break;
		case COPY_INT_INT:
			copy(bytes, output, &readIndex, insn->data.copyIntInt.offset, insn->data.copyIntInt.length);
			break;
		case COPY_LONG_INT:
			copy(bytes, output, &readIndex, insn->data.copyLongInt.offset, insn->data.copyLongInt.length);
			break;
		}
		
		free(insn);
	}
	
	
}

static void append(vector<char>& output, int length, FILE *src) {
	char *data = malloc(length);
	fread(data, 1, length, src);
	
	write(output, length, data);
	
	free(data);
}

static void copy(vector<char>& source, vector<char>& output, int *readIndex, long offset, int length) {
	skip(readIndex, source, offset);
	
	char *toCopy = read(readIndex, source, length);
	write(output, length, toCopy);
	free(toCopy);
}

static void skip(int *index, vector<char>& input, long length) {
	char *ptr = read(index, input, length);
	free(ptr);
}

static char *read(int *index, vector<char>& input, long length) {
	char *data = (char *) malloc(length);
	
	long i;
	for (i = 0; i < length; i++)
		data[i] = input[i+(*index)];
	
	(*index) += length;
	return data;
}

static void write(vector<char>& output, int length, const char *value) {
	int i;
	for (i = 0; i < length; i++)
		output.push_back(value[i]);
}
