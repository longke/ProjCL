/*
 *  projcl_types.h
 *  Magic Maps
 *
 *  Created by Evan Miller on 2/12/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#define PL_FLOAT_VECTOR_SIZE 8
#define ck_padding(n, size) (((n)+(size)-1)/(size)*(size))

typedef enum PLDatum {
    PL_DATUM_WGS_84,
    PL_DATUM_WGS_72,
    PL_DATUM_ED_50,
    PL_DATUM_ED_79,
    PL_DATUM_ED_87,
    PL_DATUM_AUSTRIA_NS,
    PL_DATUM_BELGIUM_50,
    PL_DATUM_BERNE_1873,
    PL_DATUM_CH_1903,
    PL_DATUM_DANISH_GI_1934,
    PL_DATUM_NOUV_TRIG_DE_FRANCE_GREENWICH,
    PL_DATUM_NOUV_TRIG_DE_FRANCE_PARIS,
    PL_DATUM_POTSDAM,
    PL_DATUM_GGRS_87,
    PL_DATUM_HJORSEY_55,
    PL_DATUM_IRELAND_65,
    PL_DATUM_ITALY_1940,
    PL_DATUM_NOUV_TRIG_DE_LUX,
    PL_DATUM_NETHERLANDS_1921,
    PL_DATUM_OSGB_36,
    PL_DATUM_PORTUGAL_DLX,
    PL_DATUM_PORTUGAL_1973,
    PL_DATUM_RNB_72,
    PL_DATUM_RT_90,
    PL_DATUM_NAD_27,
    PL_DATUM_NAD_83
} PLDatum;

typedef enum PLSpheroid {
	PL_SPHEROID_SPHERE,
	PL_SPHEROID_WGS_84,
    PL_SPHEROID_GRS_80,
    PL_SPHEROID_AIRY_1830,
    PL_SPHEROID_AIRY_1848,
    PL_SPHEROID_MODIFIED_AIRY,
    PL_SPHEROID_BESSEL_1841,
    PL_SPHEROID_CLARKE_1866,
    PL_SPHEROID_GRS_1967_TRUNCATED,
    PL_SPHEROID_WGS_84_MAJOR_AUXILIARY_SPHERE
} PLSpheroid;

typedef enum PLImageFilter {
    PL_IMAGE_FILTER_NEAREST_NEIGHBOR,
    PL_IMAGE_FILTER_BILINEAR,
    PL_IMAGE_FILTER_BICUBIC,
    PL_IMAGE_FILTER_QUASI_BICUBIC
} PLImageFilter;

#define PL_MODULE_DATUM                         (1 << 1)
#define PL_MODULE_GEODESIC                      (1 << 2)
#define PL_MODULE_WARP                          (1 << 3)
#define PL_MODULE_ALBERS_EQUAL_AREA             (1 << 4)
#define PL_MODULE_AMERICAN_POLYCONIC            (1 << 5)
#define PL_MODULE_LAMBERT_AZIMUTHAL_EQUAL_AREA  (1 << 6)
#define PL_MODULE_LAMBERT_CONFORMAL_CONIC       (1 << 7)
#define PL_MODULE_MERCATOR                      (1 << 8)
#define PL_MODULE_ROBINSON                      (1 << 9)
#define PL_MODULE_TRANSVERSE_MERCATOR           (1 << 10)
#define PL_MODULE_WINKEL_TRIPEL                 (1 << 11)

#define PL_MODULE_PROJECTION                    (0xFFFF - 7)

#define PL_MODULE_NEAREST_NEIGHBOR              (1 << 24)
#define PL_MODULE_BILINEAR                      (1 << 25)
#define PL_MODULE_BICUBIC                       (1 << 26)
#define PL_MODULE_QUASI_BICUBIC                 (1 << 27)

#define PL_MODULE_FILTER                        (0xF << 24)

typedef struct PLCode_s {
	unsigned char		*binary;
	size_t	     len;
	cl_uint      kernel_count;
} PLCode;

typedef struct PLSpheroidInfo_s {
	PLSpheroid   tag;
	float		major_axis;
	float		minor_axis;
	float		ecc;
	float		ecc2;
	float		one_ecc2;
	float		ec;
	float		inverse_flattening;
	float		en[8];
} PLSpheroidInfo;

typedef struct PLContext_s {
	cl_context		 ctx;
	cl_command_queue queue;
	cl_device_id     device_id;
	cl_uint		     kernel_count;
	cl_kernel	    *kernels;
} PLContext;

typedef struct PLProjectionBuffer_s {
	cl_mem      xy_in;
	cl_mem      xy_out;
	cl_uint	    count;
} PLProjectionBuffer;

typedef struct PLDatumShiftBuffer_s {
    cl_mem      x_rw;
    cl_mem      y_rw;
    cl_mem      z_rw;
    cl_mem      xy_in;
    cl_mem      xy_out;
    cl_uint     count;
} PLDatumShiftBuffer;

typedef struct PLForwardGeodesicFixedDistanceBuffer_s {
	cl_mem	    xy_in;
	cl_uint     xy_count;
	cl_mem	    az_in;
	cl_uint     az_count;
	cl_mem	    phi_sincos;
	cl_mem      az_sincos;
	cl_mem      xy_out;
} PLForwardGeodesicFixedDistanceBuffer;

typedef struct PLForwardGeodesicFixedAngleBuffer_s {
	cl_mem	    dist_in;
	cl_uint     dist_count;
	cl_mem      xy_out;
} PLForwardGeodesicFixedAngleBuffer;

typedef struct PLInverseGeodesicBuffer_s {
	cl_mem      xy1_in;
	cl_uint     xy1_count;
	cl_mem      xy2_in;
	cl_uint     xy2_count;
	cl_mem      dist_out;
} PLInverseGeodesicBuffer;

typedef struct PLImageBuffer_s {
    cl_mem      image;
    cl_image_format image_format;
    size_t      width;
    size_t      height;
    size_t      row_pitch;
} PLImageBuffer;

typedef struct PLImageArrayBuffer_s {
    cl_mem      image;
    cl_image_format image_format;
    size_t      width;
    size_t      height;
    size_t      depth;
    size_t      tiles_across;
    size_t      tiles_down;
    size_t      row_pitch;
    size_t      slice_pitch;
} PLImageArrayBuffer;

typedef struct PLPointGridBuffer_s {
    cl_mem      grid;
    size_t      width;
    size_t      height;
} PLPointGridBuffer;
