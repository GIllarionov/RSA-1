/*!
     \brief Математические операции с длинными числами
 */
class math
{
public:
    /*!
    Умножает одно длинное целое число на второе
    \param[in] a Первый множитель
    \param[in] b Второй множитель
    \param[out] c Произведение будет записано сюда
    \param[in] len Длина чисел в блоках по 32 бита (для всех чисел одинакова)
    */
    static auto multiply(const unsigned long long *a, const unsigned long long *b, unsigned long long *c,int len) {
        int i,j;
        unsigned long long t;
        for (i=0; i<len; ++i) c[i]=0;
        for (i=0; i<(len/2); ++i) {
            for (j=0; j<(len/2); ++j){
                t = a[len-i-1]*b[len-j-1];
                c[len-i-j-1] += t % 4294967296;
                t = t/4294967296 + c[len-i-j-1]/4294967296;
                c[len-i-j-1] %= 4294967296;
                c[len-i-j-2] += t;
            }
        }
    }
    /*!
    Делит одно длинное целое число на второе
    \param[in] a Делимое
    \param[in] b Делитель
    \param[out] div Целая часть от деления будет записано сюда, если не подано nullptr
    \param[out] mod Остаток от деления будет записан сюда, если не подано nullptr
    \param[in] len Длина чисел в блоках по 32 бита (для всех чисел одинакова)
    */
    static auto divide(const unsigned long long *a, const unsigned long long *b,
                unsigned long long *div, unsigned long long *mod, int len){
        unsigned long long temp_a[len], temp_b[len];
        unsigned long long ty[len], tm[len];
        int i,j,m=0,n=0;
        bool t;
        for (i=0; i<len; ++i) {
            temp_a[i]=a[i];
            temp_b[i]=b[i];
            if (div != nullptr) div[i]=0;
            if (mod != nullptr) mod[i]=0;
        }
        for (i=0; i<len; ++i) {
            if (temp_a[i] != 0) {
                m = i;
                break;}
        }
        for (i=0; i<len; ++i) {
            if (temp_b[i] != 0) {
                n = i;
                break;}
        }
        int k = n-m;
        if (k<0) k = 0;
        for (i = 0; i < len-k; ++i) temp_b[i] = temp_b[i+k];
        for (i = 0; i < k; ++i) temp_b[len-i-1] = 0;
        for (i = 0; i<k+1; ++i) {
            unsigned long long r = 0, left = 0, right = 4294967296;
            while (left <= right) {
                unsigned long long mid = (left+right)/2;
                for (j = 0; j<len; ++j) {
                    ty[j] = 0;
                    tm[j] = 0;
                }
                tm[len-1] = mid;
                multiply(temp_b,tm,ty,len);
                t = true;
                for (j = 0; j < len; ++j) {
                    if (ty[j] > temp_a[j]) {
                        t = false;
                        break;
                    }
                    if (ty[j] < temp_a[j]) break;
                }
                if (t) {
                    r = mid;
                    left = mid+1;
                } else right = mid -1;
            }
            for (j = 0; j<len; ++j) tm[j]=0;
            tm[len-1] = r;
            multiply(temp_b,tm,ty,len);
            int u;
            for (u = 0; u<len; ++u) {
                if (ty[len-u-1]>temp_a[len-u-1]) {
                    int v = 1;
                    while (temp_a[len-u-v-1] == 0) {
                        temp_a[len-u-v-1] = 4294967295;
                        v+=1;
                    }
                    temp_a[len-u-v-1] -= 1;
                    temp_a[len-u-1] = 4294967296 + temp_a[len-u-1] - ty[len-u-1];
                } else temp_a[len-u-1] -= ty[len-u-1];
            }
            if(k-i >0){
                for(j=0;j<len-1;++j) temp_b[len-j-1] = temp_b[len-j-2];
            }
            if (div != nullptr) div[len-(k-i)-1] = r;
        }
        if (mod != nullptr) {
            for (i = 0; i < len; ++i) mod[i] = temp_a[i];
        }
    }
    /*!
    Сравнивает одно длинное целое число со вторым
    \param[in] a Первое число
    \param[in] b Второе число
    \param[in] len Длина чисел в блоках по 32 бита (для всех чисел одинакова)
    \return Больше (или равно) ли первое число и второе
    */
    static bool is_bigger(const unsigned long long *a, const unsigned long long *b, int len) {
        int i;
        bool res = true;
        for (i=0; i<len; ++i) {
            if (a[i] < b[i]) {
                res = false;
                break;
            } else {
                if (a[i] > b[i]) break;
            }
        }
        return  res;
    }
    /*!
    Складывает одно длинное целое число со вторым
    \param[in] a Первое слагаемое
    \param[in] b Второе слагаемое
    \param[in] len Длина чисел в блоках по 32 бита (для всех чисел одинакова)
    \param[out] res Сумма
    */
    static auto sum(const unsigned long long *a, const unsigned long long *b, unsigned long long *res, int len){
        int i;
        unsigned long long t;
        for (i=len-1; i>=0; --i) {
            t = res[i] + a[i] + b[i];
            res[i] = t % 4294967296;
            if (i>0) res[i-1] = t / 4294967296;
        }
    }
    /*!
    Вычитает второе число из первого (со знаком). Первый элемент числа - его знак (0 - "+"; 1 - "-")
    \param[in] a Первое число
    \param[in] b Второе число
    \param[in] len Длина чисел в блоках по 32 бита (для всех чисел одинакова, но не учитывает знак)
    \param[out] res Разность
    */
    static auto sub(const unsigned long long *a, const unsigned long long *b,
             unsigned long long *res,int len) {
        int i, v=0;
        unsigned long long t, a1[len-1], b1[len-1], r1[len-1];
        for (i=0; i<len-1; ++i) {
            a1[i] = a[i+1];
            b1[i] = b[i+1];
            r1[i] = 0;
        }
        if (a[0] != b[0]) {
            sum(a1,b1,r1,len-1);
            res[0] = a[0];
            for (i=0; i<len-1; ++i) {
                res[i+1] = r1[i];
            }
            return 0;
        } else {
            if (is_bigger(a1,b1,len-1)){
                res[0] = a[0];
            } else {
                if (a[0] == 0) res[0] = 1;
                else res[0] = 0;
                for (i = 0; i < len-1; ++i) {
                    t = a1[i];
                    a1[i] = b1[i];
                    b1[i] = t;
                }
            }
        }
        for (i=len-2; i>=0; --i) {
            t = a1[i];
            if (a1[i]<b1[i]) {
                t += 4294967296;
                v = i-1;
            } else v = -1;
            r1[i] = t - b1[i];
            if (v >=0) {
                while (a1[v] == 0 && v >= 0) {
                    a1[v] = 4294967295;
                    v -= 1;
                }
                a1[v] -= 1;
            }
        }
        for (i = 0; i < len-1; ++i) res[i+1] = r1[i];
        return 0;
    }
    /*!
    Находит для двух чисел коэффициенты (x,y) Безу, такие, что НОД(a,b) = x*a +y*b
    \param[in] a Первое число
    \param[in] b Второе число
    \param[out] x Коэффициент перед a (со знаком)
    \param[out] y Коэффициент перед b (со знаком)
    \param[in] len Длина чисел в блоках по 32 бита (для всех чисел одинакова, но не учитывает знак)
    */
    static auto bezout(const unsigned long long *a, const unsigned long long *b,
                unsigned long long *x, unsigned long long *y, int len) {
        int i;
        for (i = 1; i <len+1; ++i) {
            if (a[i] != 0) break;
            if (i == len) {
                x[len] = 0;
                y[len] = 1;
                return 0;
            }
        }
        unsigned long long x1[len+1], y1[len+1], bda[len],m1[len+1];
        for (i = 0; i <len; ++i) {
            x1[i] = 0;
            y1[i] = 0;
            bda[i] = 0;
        }
        x1[len] = 0;
        y1[len] = 0;
        divide(b,a, nullptr,bda,len);
        bezout(bda,a,x1,y1,len);
        unsigned long long div[len], module[len], mx1[len];
        divide(b,a, div, nullptr, len);
        for (i = 0; i<len; ++i) mx1[i] = x1[i+1];
        multiply(div,mx1,module,len);
        m1[0] = x1[0];
        for (i = 0; i< len + 1; ++i) {
            y[i] = x1[i];
            x[i] = 0;
        }
        for (i = 0; i< len; ++i) m1[i+1] = module[i];
        sub(y1, m1, x, len+1);
        return 0;
    }
    /*!
    Возводит число в степень по модулю
    \param[in] base Основание
    \param[in] pow Степень
    \param[in] mod Модуль
    \param[out] res Результат
    \param[in] len Длина чисел в блоках по 32 бита (для всех чисел одинакова)
    */
    static auto mod_pow(const unsigned long long *base, const unsigned long long *pow,
                 unsigned long long *mod, unsigned long long *res, int len) {
        int i,j;
        int bin_pow[len*32];
        unsigned long long temp_pow[len];
        for (i = 0; i<len; ++i) temp_pow[i] = pow[i];
        for (i = 0; i<len; ++i) {
            for (j = 0; j<32; ++j){
                bin_pow[i*32+32-j-1] = int(temp_pow[i] % 2);
                temp_pow[i] /= 2;
            }
        }
        unsigned long long p2[len*32][len], temp_base[len], temp_base1[len];
        for (i = 0; i < len; ++i) temp_base[i] = base[i];
        for (i = 0; i < len*32; ++i) {
            divide(temp_base, mod, nullptr, temp_base1, len);
            for (j = 0; j<len; ++j) {
                p2[i][j] = temp_base1[j];
                temp_base[j] = temp_base1[j];
            }
            multiply(temp_base,temp_base, temp_base1, len);
            for (j = 0; j<len; ++j) temp_base[j] = temp_base1[j];
        }
        for (i=0; i<len; ++i) res[i] = 0;
        res[len-1] = 1;
        for (i=0; i<len*32; ++i) {
            if (bin_pow[len*32-i-1] == 1) {
                unsigned long long temp_res[len];
                multiply(res, p2[i], temp_res, len);
                divide(temp_res, mod, nullptr, res, len);
            }
        }
    }

};
