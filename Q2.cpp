#include "stdio.h"
#include "x86intrin.h"

typedef union
{
	__m128i 			int128;
	
	unsigned char		m128_u8[16];
	signed char			m128_i8[16];

	unsigned short		m128_u16[8];
	signed short		m128_i16[8];

	unsigned long		m128_u32[4];
	signed long			m128_i32[4];

	unsigned long long	m128_u64[2];
	signed long long	m128_i64[2];
} intVec;

typedef union
{
	__m128 		sp128;
	
	float		m128_sp[4];
} spVec;

void print_int_vector(__m128i a, unsigned char type)
{
	/*u8 : 1
	i8 : 2
	u16 : 3
	i16 : 4
	u32 : 5
	i32 : 6
	u64 : 7
	i64 : 8*/
	intVec tmp;
	tmp.int128 = a;
	printf ("[");
	switch(type)
	{
		case'1':
			for (int i=15; i>0; i--)
			{
				printf ("%X, ", tmp.m128_u8[i]);
			}
			printf ("%X]\n\n", tmp.m128_u8[0]);
			break;
		case'2':
			for (int i=15; i>0; i--)
			{
				printf ("%d, ", tmp.m128_i8[i]);
			}
			printf ("%d]\n\n", tmp.m128_i8[0]);
			break;
		case'3':
			for (int i=7; i>0; i--)
			{
				printf ("%X, ", tmp.m128_u16[i]);
			}
			printf ("%X]\n\n", tmp.m128_u16[0]);
			break;
		case'4':
			for (int i=7; i>0; i--)
			{
				printf ("%d, ", tmp.m128_i16[i]);
			}
			printf ("%d]\n\n", tmp.m128_i16[0]);
			break;
		case'5':
			for (int i=3; i>0; i--)
			{
				printf ("%lu, ", tmp.m128_u32[i]);
			}
			printf ("%lu]\n\n", tmp.m128_u32[0]);
			break;
		case'6':
			for (int i=3; i>0; i--)
			{
				printf ("%ld, ", tmp.m128_i32[i]);
			}
			printf ("%ld]\n\n", tmp.m128_i32[0]);
			break;
		case'7':
			printf ("%llu, ", tmp.m128_u64[1]);
			printf ("%llu]\n\n", tmp.m128_u64[0]);
			break;
		case'8':
			printf ("%lld, ", tmp.m128_i64[1]);
			printf ("%lld]\n\n", tmp.m128_i64[0]);
			break;
	}
}

void print_spfp_vector(__m128 a)
{
	spVec tmp;
	tmp.sp128 = a;
	printf ("[");
	for (int i=3; i>0; i--)
		{
			printf ("%f, ", tmp.m128_sp[i]);
		}
	printf ("%f]\n\n", tmp.m128_sp[0]);
}


unsigned char intArray [16] = {	0X00, 0X11, 0X22, 0X33, 0X44, 0X55, 0X66, 0X77,
								0X88, 0X99, 0XAA, 0XBB, 0XCC, 0XDD, 0XEE, 0XFF};
float spArray [4] =  {	1.5, 5.75, 54.25, 30.0};

int main(void)
{
	__m128i a;
	__m128 b;
	a = _mm_load_si128((const __m128i*)intArray);
	b = _mm_load_ps((const float*)spArray);

	printf ("Unsigned byte: ");
	print_int_vector(a,'1');

	printf ("Signed byte: ");
	print_int_vector(a,'2');

	printf ("Unsigned word: ");
	print_int_vector(a,'3');

	printf ("Signed word: ");
	print_int_vector(a,'4');

	printf ("Unsigned double word: ");
	print_int_vector(a,'5');

	printf ("Signed double word: ");
	print_int_vector(a,'6');

	printf ("Unsigned quad word: ");
	print_int_vector(a,'7');

	printf ("Signed quad word: ");
	print_int_vector(a,'8');

	printf ("Single precision FP: ");
	print_spfp_vector(b);
	
	return 0;
}