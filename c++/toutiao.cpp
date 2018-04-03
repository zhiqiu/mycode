//实现memcpy库函数  
void* memcpy(void *dst, const void *src, size_t count){  
    // 容错处理  
    if(dst == NULL || src == NULL){  
        return NULL;  
    }  
    unsigned char *pdst = (unsigned char *)dst;  
    const unsigned char *psrc = (const unsigned char *)src;  
    //判断内存是否重叠  
    bool flag1 = (pdst >= psrc && pdst < psrc + count);  
    bool flag2 = (psrc >= pdst && psrc < pdst + count);  
    if(flag1 || flag2){  
        cout<<"内存重叠"<<endl;  
        return NULL;  
    }  
    // 拷贝  
    while(count--){  
        *pdst = *psrc;  
        pdst++;  
        psrc++;  
    }  
    return dst;  
}  
