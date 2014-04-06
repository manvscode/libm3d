#ifndef _TEST_H_
#define _TEST_H_


#define COLOR_BEGIN(bg,fg)                    "\e[" #bg ";" #fg "m"
#define COLOR_END                             "\e[m"
#define COLOR_TOKEN(color_bg, color_fg, tok)  COLOR_BEGIN(color_bg, color_fg) #tok COLOR_END
#define COLOR_STRING(color_bg, color_fg, str) COLOR_BEGIN(color_bg, color_fg) str COLOR_END

#define COLOR_GREEN                           COLOR_BEGIN(0,32)
#define COLOR_RED                             COLOR_BEGIN(0,31)
#define COLOR_YELLOW                          COLOR_BEGIN(0,33)
#define COLOR_BLUE                            COLOR_BEGIN(0,34)
#define COLOR_MAGENTA                         COLOR_BEGIN(0,35)
#define COLOR_CYAN                            COLOR_BEGIN(0,36)
#define COLOR_WHITE                           COLOR_BEGIN(0,37)

#define COLOR_GREEN_STR(s)                    COLOR_STRING(0,32,s)
#define COLOR_YELLOW_STR(s)                   COLOR_STRING(0,33,s)
#define COLOR_RED_STR(s)                      COLOR_STRING(0,31,s)
#define COLOR_CYAN_STR(s)                     COLOR_STRING(0,36,s)

typedef bool (*test_fxn)( void );

static inline bool test_eval_feature( unsigned int i, const char* feature, test_fxn test )
{
	bool is_passed = test();
	printf( "%s%5u%s: %s... %s\n", COLOR_CYAN, i, COLOR_END, feature, is_passed ? COLOR_GREEN_STR("ok") : COLOR_RED_STR("failed") );
	return is_passed;
}

typedef struct test_feature {
	const char* feature;
	test_fxn    function;
} test_feature_t;



static inline bool test_eval_features( const char* suite, const test_feature_t features[], size_t count )
{
	bool is_passed = true;

	size_t len = strlen(suite);
	size_t half_len = len / 2;
	int w = 10;
	printf( "%s: %s%-30s%s\n", COLOR_CYAN_STR("Suite"), COLOR_YELLOW, suite, COLOR_END );
	for( size_t i = 0; is_passed && i < count; i++ )
	{
		is_passed = test_eval_feature( i + 1, features[ i ].feature, features[ i ].function );
	}

	printf( "----------------------\n" );
	printf( "%sOverall%s: %s\n\n", COLOR_CYAN, COLOR_END, is_passed ? COLOR_GREEN_STR("PASSED.") : COLOR_RED_STR("FAILED.") );

	return is_passed;
}



#endif /* _TEST_H_ */
