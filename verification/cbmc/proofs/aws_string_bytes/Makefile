# Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
# SPDX-License-Identifier: Apache-2.0.

include ../Makefile.aws_string

CBMCFLAGS +=

HARNESS_ENTRY = aws_string_bytes_harness
HARNESS_FILE = $(HARNESS_ENTRY).c

PROOF_SOURCES += $(HARNESS_FILE)
PROOF_SOURCES += $(PROOF_SOURCE)/make_common_data_structures.c
PROOF_SOURCES += $(PROOF_SOURCE)/proof_allocators.c

PROJECT_SOURCES += $(SRCDIR)/source/string.c

include ../Makefile.common
