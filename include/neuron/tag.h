/**
 * NEURON IIoT System for Industry 4.0
 * Copyright (C) 2020-2022 EMQ Technologies Co., Ltd All rights reserved.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
config_ **/

#ifndef NEURON_TAG_H
#define NEURON_TAG_H

#include <stdbool.h>
#include <stdint.h>

#include "utils/utextend.h"

#include "type.h"

typedef enum {
    NEU_ATTRIBUTE_READ      = 1,
    NEU_ATTRIBUTE_WRITE     = 2,
    NEU_ATTRIBUTE_SUBSCRIBE = 4,
} neu_attribute_e;

typedef struct {
    char *          name;
    char *          address;
    char *          description;
    neu_attribute_e attribute;
    neu_type_e      type;
} neu_datatag_t;

UT_icd *neu_tag_get_icd();

typedef enum {
    NEU_DATATAG_ENDIAN_L16  = 0, // #L
    NEU_DATATAG_ENDIAN_B16  = 1, // #B
    NEU_DATATAG_ENDIAN_LL32 = 2, // #LL
    NEU_DATATAG_ENDIAN_LB32 = 3, // #LB
    NEU_DATATAG_ENDIAN_BB32 = 4, // #BB
    NEU_DATATAG_ENDIAN_BL32 = 5, // #BL
} neu_datatag_endian_e;

typedef enum {
    NEU_DATATAG_STRING_TYPE_H = 0, // high-to-low endian
    NEU_DATATAG_STRING_TYPE_L = 1, // low-to-high endian
    NEU_DATATAG_STRING_TYPE_D = 2, // a high byte is stored in an int16
    NEU_DATATAG_STRING_TYPE_E = 3, // a low byte is stored in an int16
} neu_datatag_string_type_e;

typedef union {
    struct {
        neu_datatag_endian_e endian;
    } value16;
    struct {
        neu_datatag_endian_e endian;
    } value32;
    struct {
        uint16_t                  length;
        neu_datatag_string_type_e type;
    } string;

    struct {
        uint8_t bit;
    } bit;
} neu_datatag_addr_option_u;

int neu_datatag_parse_addr_option(neu_datatag_t *            datatag,
                                  neu_datatag_addr_option_u *option);

bool neu_datatag_string_is_utf8(char *data, int len);

int neu_datatag_string_htol(char *str, int len);
int neu_datatag_string_ltoh(char *str, int len);
int neu_datatag_string_etod(char *str, int len);
int neu_datatag_string_dtoe(char *str, int len);
int neu_datatag_string_etoh(char *str, int len);
int neu_datatag_string_dtoh(char *str, int len);
int neu_datatag_string_tod(char *str, int len, int buf_len);
int neu_datatag_string_toe(char *str, int len, int buf_len);

#endif