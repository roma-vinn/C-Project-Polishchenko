# Project_C_Polishchenko
Виконав: Поліщенко Роман.

Назва: Geometry2D.

Завдання: Структури ТОЧКА(Point2D), ВІДРІЗОК(Segment2D), ТРИКУТНИК (Triangle2D), ПРЯМА(Line2D). Точка – це структура двох дійсних чисел(x,y), відрізок – дві точки(a,b), трикутник – три точки(a,b,c), пряма задається 3 числами(Dtype a,b,c). Стандартні функції –(додавання – це додавання векторів, множення – векторний та скалярний добуток mult,multS). Функції перетину відрізків (повертає точку або нічого), відрізку та прямих, прямих. Point2D(INF,INF) – це нескінчено багато точок, Point2D(INF,-INF) – це немає точок.
Point2D intersect(Segment2D p1, Segment2D p2);
Point2D intersect (Line2D p1, Segment2D p2);
Point2D intersect (Line2D p1, Line2D p2);

Функції площа трикутнику(area), периметр трикутнику(perimeter), центр(center_circle) та радіуси вписаного/описаного кола, кути трикутника(angleA(),angleB(),angleC()). Рівняння медіани(Line2D medianA(Triangle2D x)), бісектриси, висоти для даної вершини, центр мас трикутника center(). Знайти площі фігур на які відсікає пряма з трикутника.

