#define ESPACO_NUMERO 8
#define ESC_NUMERO 27

#ifdef __APPLE__
#define SETA_CIMA_NUMERO 115
#define SETA_BAIXO_NUMERO 119
#define ENTER_NUMERO 10
#elif defined(_WIN32) || defined(WIN32)
#define SETA_CIMA_NUMERO 80
#define SETA_BAIXO_NUMERO 72
#define ENTER_NUMERO 13
#endif
