#pragma once

INT     APIENTRY  BITMAP_GetObject(SURFACE * bmp, INT count, LPVOID buffer);
HBITMAP FASTCALL BITMAP_CopyBitmap (HBITMAP  hBitmap);

BOOL
NTAPI
GreSetBitmapOwner(
    _In_ HBITMAP hbmp,
    _In_ ULONG ulOwner);

HBITMAP
NTAPI
GreCreateBitmap(
    _In_ ULONG nWidth,
    _In_ ULONG nHeight,
    _In_ ULONG cPlanes,
    _In_ ULONG cBitsPixel,
    _In_opt_ PVOID pvBits);

HBITMAP
NTAPI
GreCreateBitmapEx(
    _In_ ULONG nWidth,
    _In_ ULONG nHeight,
    _In_ ULONG cjWidthBytes,
    _In_ ULONG iFormat,
    _In_ USHORT fjBitmap,
    _In_ ULONG cjSizeImage,
    _In_opt_ PVOID pvBits,
    _In_ FLONG flags);

HBITMAP
NTAPI
GreCreateCompatibleBitmap(
    HDC hDC,
    INT Width,
    INT Height);

HBITMAP
NTAPI
GreCreateDIBitmapReal(
    _In_ HDC hDC,
    _In_ DWORD InitFlags,
    _In_ OPTIONAL VOID* InitData,
    _In_ OPTIONAL const BITMAPINFO* BmInfo,
    _In_ DWORD Usage,
    _In_ UINT BmInfoSize,
    _In_ UINT ContentSize,
    _In_ void* Unknown1,
    _In_ UINT Unknown2,
    _In_ void* Unknown3,
    _In_ char UnknownFlags,
    _In_ UINT Unknown4,
    _In_ INT Unknown5);

HBITMAP
NTAPI
GreCreateDIBitmapComp(
    _In_ HDC hDC,
    _In_ INT Width,
    _In_ INT Height,
    _In_ DWORD InitFlags,
    _In_ OPTIONAL VOID* InitData,
    _In_ OPTIONAL const BITMAPINFO* BmInfo,
    _In_ DWORD Usage,
    _In_ UINT BmInfoSize,
    _In_ UINT ContentSize,
    _In_ DWORD Unused,
    _In_ HANDLE XForm);

HBITMAP
NTAPI
GreCreateDIBitmapInternal(
    IN HDC hDc,
    IN INT cx,
    IN INT cy,
    IN DWORD fInit,
    IN OPTIONAL LPBYTE pjInit,
    IN OPTIONAL PBITMAPINFO pbmi,
    IN DWORD iUsage,
    IN FLONG fl,
    IN UINT cjMaxBits,
    IN HANDLE hcmXform);

void*
NTAPI
GreSetDIBitsInternal(
    _In_ HDC hDC,
    _In_ HBITMAP Bitmap,
    _In_ INT Width,
    _In_ INT Height,
    _In_ void* InitData,
    _In_ const BITMAPINFO* BmInfo,
    _In_ DWORD Usage,
    _In_ UINT ContentSize,
    _In_ UINT BmInfoSize,
    _In_ HANDLE XForm);

BOOL
NTAPI
GreGetBitmapDimension(
    _In_ HBITMAP hBitmap,
    _Out_ LPSIZE psizDim);

UINT
NTAPI
GreGetBitmapSize(
    _In_ const BITMAPINFO* BmInfo,
    _In_ DWORD Usage);
