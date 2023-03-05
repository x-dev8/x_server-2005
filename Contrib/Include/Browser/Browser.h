#ifndef BROWSER_H
#define BROWSER_H

#ifdef __cplusplus
extern "C" {
#endif

extern long EmbedBrowserObject(HWND hwnd);
extern void ResizeBrowser(HWND hwnd, DWORD width, DWORD height);
extern long DisplayHTMLPage(HWND hwnd, LPTSTR webPageName);
extern long DisplayHTMLStr(HWND hwnd, LPCTSTR string);
extern void DoPageAction(HWND hwnd, DWORD action);
extern void UnEmbedBrowserObject(HWND hwnd);

#ifdef __cplusplus
}
#endif

#endif