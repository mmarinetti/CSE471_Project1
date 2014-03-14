#include "StdAfx.h"
#include <cstdlib>     /* srand, rand */
#include <time.h>       /* time */
#include "Noise.h"
#include <cmath>

CNoise::CNoise(void)
{
    
}

CNoise::~CNoise(void)
{
}


void CNoise::Start()
{
    m_phase = 0;
}

bool CNoise::Generate()
{
    double sample = 0;
    sample = ((double(rand()) / double(RAND_MAX)) * (1)) - .5;

    m_frame[0]=m_frame[1]=sample*.5;

    return true;
}