# Практическая часть
---
Рефакторим калькулятор!
---

Делаем класс, теперь вместо передачи результата через функции можно использовать поля класса
Добавляем скобки ( )
Добавляем константы, например Pi
Пример выражений:

---

```
(5 + 3 * (8 / Pi) * 4) + (1)
```

Из контант пусть пока будет только Pi (3.14) и e (2.7). Для констант можно использовать std::unordered_map:

```
#include <unordered_map>

std::unordered_map<std::string, double> contants = 
    {
        { "Pi", 3.14 },
        { "e", 2.7 }
    };
```

EOF