/* Copyright (C) 2013-2015 by Joseph A. Marrero, http://www.manvscode.com/
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include "algorithms.h"

#if 0
#define hidx(w,t) (workers * (t) + (w))
#else
#define hidx(w,t) (tasks * (w) + (t))
#endif
static inline void dump_matrix( int cost[], size_t workers, size_t tasks )
{
	for( size_t t = 0; t < tasks; t++ )
	{
		for( size_t w = 0; w < workers; w++ )
		{
			printf( "%3d ", cost[ hidx(w, t) ] );
		}
		printf( "\n" );
	}
	printf( "\n" );
}
static inline void dump_array( const char* label, int array[], size_t count )
{
	printf( "%s = {", label );
	for( size_t i = 0; i < count - 1; i++ )
	{
		printf( "%d, ", array[ i ] );
	}

	printf( "%d}\n", array[ count - 1 ] );
}

static void minimal_hungarian_assignment( int cost[], size_t workers, size_t tasks, int output[] );
static bool is_optimal_hungarian_assignment( int cost[], size_t workers, size_t tasks, int cols[], int rows[], size_t* lines );


void hungarian_assignment( bool maximal, int cost[], size_t workers, size_t tasks, int output[] )
{
	dump_matrix( cost, workers, tasks );
	if( maximal )
	{
		size_t count = workers * tasks;
		int max = cost[ 0 ];

		/* Find max value */
		for( size_t i = 1; i < count; i++ )
		{
			if( max < cost[ i ] )
			{
				max = cost[ i ];
			}
		}

		/* Convert maximal values to minimal values */
		for( size_t i = 0; i < count; i++ )
		{
			cost[ i ] = max - cost[ i ];
		}
	}

	minimal_hungarian_assignment( cost, workers, tasks, output );
}

void minimal_hungarian_assignment( int cost[], size_t workers, size_t tasks, int output[] )
{
	int cols[ workers ];
	int rows[ tasks ];
	size_t lines = 0;

	memset( cols, 0, sizeof(cols) );
	memset( rows, 0, sizeof(rows) );

	/* Minimize rows */
	for( size_t t = 0; t < tasks; t++ )
	{
		if( !rows[ t ] )
		{
			int optimal = cost[ hidx(0, t) ];

			for( size_t w = 1; w < workers; w++ )
			{
				if( optimal > cost[ hidx(w, t) ] )
				{
					optimal = cost[ hidx(w,  t) ];
				}
			}

			if( optimal > 0 )
			{
				for( size_t w = 0; w < workers; w++ )
				{
					cost[ hidx(w, t) ] -= optimal;
				}
			}
		}
	}

	/* Minimize columns */
	for( size_t w = 0; w < workers; w++ )
	{
		if( !cols[ w ] )
		{
			int optimal = cost[ hidx(w, 0) ];

			for( size_t t = 1; t < tasks; t++ )
			{
				if( optimal > cost[ hidx(w, t) ] )
				{
					optimal = cost[ hidx(w, t) ];
				}
			}

			if( optimal > 0 )
			{
				for( size_t t = 0; t < tasks; t++ )
				{
					cost[ hidx(w, t) ] -= optimal;
				}
			}
		}
	}

	while( !is_optimal_hungarian_assignment( cost, workers, tasks, cols, rows, &lines ) )
	{
		int min = INT_MAX;

		for( size_t t = 0; t < tasks; t++ )
		{
			for( size_t w = 0; w < workers; w++ )
			{
				if( !rows[ t ] && !cols[ w ] )
				{
					if( cost[ hidx(w, t) ] < min )
					{
						min = cost[ hidx(w, t) ];
					}
				}
			}
		}

		for( size_t t = 0; t < tasks; t++ )
		{
			for( size_t w = 0; w < workers; w++ )
			{
				if( !rows[ t ] && !cols[ w ] )
				{
					cost[ hidx(w, t) ] -= min;
				}
				else if( rows[ t ] && cols[ w ] )
				{
					cost[ hidx(w, t) ] += min;
				}
			}
		}
	}

	dump_matrix( cost, workers, tasks );

#if 1
	for( size_t w = 0; w < workers; w++ )
	{
		output[ w ] = w;
	}

	for( size_t w = 0; w < workers; w++ )
	{
		if( cost[ hidx(w,w) ] != 0 )
		{
			bool done = false;

			//for( size_t t = 0; !done && t < tasks; t++ )
			for( size_t t = 0; !done && t < tasks; t++ )
			{
				if( cost[ hidx(w,t) ] == 0 )
				{
					if( t != w )
					{
						/* Swap task rows */
						for( size_t i = 0; i < workers; i++ )
						{
							int tmp = cost[ hidx(i, t) ];
							cost[ hidx(i, t) ] = cost[ hidx(i, w) ];
							cost[ hidx(i, w) ] = tmp;
						}
						int tmp = output[ w ];
						output[ w ] = output[ t ];
						output[ t ] = tmp;
					}

					//done = true;
				}
			}
		}

	}
#else
	size_t optimal_zeros = (workers > tasks) ? tasks : workers;

	for( size_t z = 0; z < optimal_zeros; z++ )
	{
		for( size_t t = 0; t < tasks; t++ )
		{
			for( size_t w = 0; w < workers; w++ )
			{
			}
		}
	}
#endif

	dump_matrix( cost, workers, tasks );
}

bool is_optimal_hungarian_assignment( int cost[], size_t workers, size_t tasks, int cols[], int rows[], size_t* lines )
{
	size_t optimal_lines = (workers > tasks) ? tasks : workers;
	if( *lines < optimal_lines )
	{
		int max_zeros_in_col = workers;
		int max_zeros_in_row = tasks;

		while( max_zeros_in_col > 0 && max_zeros_in_row > 0 && *lines < optimal_lines )
		{
			for( size_t t = 0; *lines < optimal_lines && t < tasks; t++ )
			{
				if( !rows[ t ] )
				{
					int zeros_found = 0;
					for( size_t w = 0; w < workers; w++ )
					{
						if( cost[ hidx(w, t) ] == 0 && !cols[ w ] && !rows[ t ] )
						{
							zeros_found += 1;
						}
					}

					if( zeros_found == max_zeros_in_row )
					{
						rows[ t ] = 1;
						*lines += 1;
					}

					#ifdef DEBUG_HUNGARIAN_ASSIGNMENT
					dump_array( "rows", rows, tasks );
					#endif
				}
			}

			for( size_t w = 0; *lines < optimal_lines && w < workers; w++ )
			{
				if( !cols[ w ] )
				{
					int zeros_found = 0;
					for( size_t t = 0; t < tasks; t++ )
					{
						if( cost[ hidx(w, t) ] == 0 && !cols[ w ] && !rows[ t ] )
						{
							zeros_found += 1;
						}
					}

					if( zeros_found == max_zeros_in_col )
					{
						cols[ w ] = 1;
						*lines += 1;
					}

					#ifdef DEBUG_HUNGARIAN_ASSIGNMENT
					dump_array( "cols", cols, workers );
					#endif
				}
			}

			/*
			if( *lines >= optimal_lines )
			{
				#ifdef DEBUG_HUNGARIAN_ASSIGNMENT
				printf( "lines = %zu\n", *lines );
				dump_array( "rows", rows, tasks );
				dump_array( "cols", cols, workers );
				#endif
				break;
			}
			*/

			max_zeros_in_col -= 1;
			max_zeros_in_row -= 1;
		}

		#ifdef DEBUG_HUNGARIAN_ASSIGNMENT
		printf( "lines = %zu\n", *lines );
		dump_array( "rows", rows, tasks );
		dump_array( "cols", cols, workers );
		#endif
	}

	return *lines >= 4;
}

