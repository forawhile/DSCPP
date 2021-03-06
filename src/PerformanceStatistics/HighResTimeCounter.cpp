//
// HighResTimeCounter.cpp
//
// 2014-08-23, Shining Yang <y.s.n@live.com>
//
#include "HighResTimeCounter.h"


CHighResTimeCounter::CHighResTimeCounter()
{
    m_bInited = ::QueryPerformanceFrequency(&m_nFrequency) ? true : false;
    m_bStarted = false;
    m_bFinished = false;
    m_nCounterBegin.QuadPart = 0;
    m_nCounterEnd.QuadPart = 0;
}

CHighResTimeCounter::~CHighResTimeCounter()
{
}

void CHighResTimeCounter::Begin()
{
    if (m_bInited && !m_bStarted) {
        m_bStarted = true;
        m_bFinished = false;
        ::QueryPerformanceCounter(&m_nCounterBegin);
    }
}

void CHighResTimeCounter::End()
{
    if (m_bStarted) {
        m_bStarted = false;
        m_bFinished = true;
        ::QueryPerformanceCounter(&m_nCounterEnd);
    }
}

LARGE_INTEGER CHighResTimeCounter::GetElapsedTimeInMicroseconds()
{
    LARGE_INTEGER nElaped;
    nElaped.QuadPart = 0;

    if (m_bFinished) {
        nElaped.QuadPart = m_nCounterEnd.QuadPart - m_nCounterBegin.QuadPart;
        nElaped.QuadPart *= 1000000;
        nElaped.QuadPart /= m_nFrequency.QuadPart;
    }
    
    return nElaped;
}

unsigned long CHighResTimeCounter::GetElapsedTimeInMS()
{
    // NOTE: conversion from 'LONGLONG' to 'unsigned long', possible loss of data
    return static_cast<unsigned long>(
        GetElapsedTimeInMicroseconds().QuadPart / 1000);
}

unsigned long CHighResTimeCounter::GetElapsedTimeInSeconds()
{
    // NOTE: conversion from 'LONGLONG' to 'unsigned long', possible loss of data
    return static_cast<unsigned long>(
        GetElapsedTimeInMicroseconds().QuadPart / 1000000);
}