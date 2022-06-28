Программа генерирует ключи шифрования в соответствии с алгоритмом RSA.
На вход подаётся требуемая длина ключа, на выход - 3 набора чисел в 16-ричной ситеме счисления.
Первое - публичная экспонента, второе - секретная экспонента, третье - модуль шифрования.
Секретный ключ формируется из секретной экспоненты и модуля, публичный - из публичной
и модуля.

Для ускорения шифрования, публичную экспоненту принято принимать равной 2^(2^n)-1, 
в данном случае она равна 65537 (10001 в HEX)

Каждое 16-ричное число соответствует 32 битам ключа.

Ссылки на источники:

https://habr.com/ru/post/534014/

http://mech.math.msu.su/~shvetz/54/inf/perl-examples/PerlExamples_FastPower_Ideas.xhtml

https://ru.algorithmica.org/cs/modular/extended-euclid/