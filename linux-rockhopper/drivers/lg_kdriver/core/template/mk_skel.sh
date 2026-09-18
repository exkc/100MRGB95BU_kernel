# SIC LABORATORY, LG ELECTRONICS INC., SEOUL, KOREA
# Copyright(c) 2013 by LG Electronics Inc.
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# version 2 as published by the Free Software Foundation.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#

#!/bin/sh
CURR_DATE=`date +%Y.%m.%d`
MOD_L=`echo $1 |awk '{printf(tolower($1))}'`
MOD_U=`echo $1 |awk '{printf(toupper($1))}'`
MODULE=$MOD_L

BASE_DIR=..
TEMPL_DIR=${BASE_DIR}/template
TEMPL_DOC_DIR=${BASE_DIR}/../doc
TEMPL_INC_DIR=${BASE_DIR}/include

DEST_DIR=${BASE_DIR}/$1
DEST_DOC_DIR=${BASE_DIR}/../doc
DEST_INC_DIR=${BASE_DIR}/${MODULE}

function check_author()
{
	return 0
}

# $1 src file (with path)
# $2 module name.
# $2 destination directory
function sed_script ()
{
	MOD_L=`basename $2 |awk '{printf(tolower($1))}'`
	MOD_U=`basename $2 |awk '{printf(toupper($1))}'`

	srcfile=`basename $1`
	dstfile=`echo $srcfile | sed -e s/template/$MOD_L/g`
	postfix=`echo $srcfile | sed -e s/template_//g`

	if [ ! -f $1 ] ; then
		echo "source template not found : $1"
		return;
	fi

	if [ -f "$3/$dstfile" ]; then
		echo " file exists $3/$dstfile, skipping..."
		return
	else
		echo "$3/$dstfile"
	fi

	sed -e s/template/$MOD_L/g 											\
		-e s/TEMPLATE/$MOD_U/g 											\
		-e s/Sample/$MOD_U/g 											\
		-e "/*  author.*modifier$/d"									\
		-e "s/*  author.*$/*  author		$AUTHOR/"					\
		-e "s/*  @author.*$/*  @author		$AUTHOR/"					\
		-e "s/*  date		20xx.*$/*  date		$CURR_DATE/"		\
 		-e "s/*  @date		20xx.*$/*  @date		$CURR_DATE/"		\
		-e "s/#	AUTHOR		:	.*$/#	AUTHOR		:	$AUTHOR/"		\
		-e "s/#	DATE        :	.*$/#	DATE        :	$CURR_DATE/"	\
		-e "s/(c) 1998-2007 by LG E/(c) 1998-2010 by LG E/"				\
		 $1  > $3/$dstfile
}

#########################################################################
# Actual Starts Here.
# generate from template to module skelenton files.
# check condition.
if [ -z "$1" ]; then
	echo Usage : `basename $0` module_name
	echo "      ---- skelenton file maker for given module (.c, .h, .dox) ----"
	echo "      this shall make..."
	echo "      .c, .h into $BASE_DIR/'module_name' using $TEMPL_DIR/.c,.h"
	echo "      'module_name'_kapi.h into $DEST_INC_DIR"
	echo "      .dox into $DEST_DOC_DIR"
	exit 0
fi

if [ ! -d $TEMPL_DIR ]; then
	echo cannot find "$TEMPL_DIR" in current directory.
	exit 0
fi

AUTHOR=$USER
check_author;

if [ ! -d $DEST_DIR ]; then
	mkdir -p $DEST_DIR
fi

for src in $TEMPL_DIR/*.[ch] $TEMPL_DIR/Makefile $TEMPL_DIR/doc.mk
do
	sed_script $src $MODULE $DEST_DIR
done

#for i in $DEST_DIR/*kapi.h
#do
#	target=${DEST_INC_DIR}/`basename $i`
#	if [[ -f $i ]]; then
#		if [[ ! -f $target ]]; then
#			echo moving $i to $target
#			mv $i $target
#		else
#			echo skipping $i
#			rm -f $i
#		fi
#	fi
#done

