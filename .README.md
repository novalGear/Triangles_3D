Вторая задача в курсе Владимирова (МФТИ) по C++.

В общем случае треугольников n штук, пока для двух:

Даны вершины двух треугольников в трехмерном пространстве (a1, b1, c1) и (a2, b2, c2), нужно определить, пересекаются они или нет. Псевдокод в виде C++ с алгоритмом решения:
``` cpp

bool check_triangles_intersection(  float vertice a1, float vertice b1, float vertice c1,
                                    float vertice a2, float vertice b2, float vertice c2) {
    // второй треугольник - задает плоскость П2
    // step1: пересекает ли первый треугольник П2?

    vec3D n = normal_vec_for_plane(a2, b2, c2); // вектор нормали к П2

    // ищем проекции векторов вида *1 - a2 на n, * in {a, b, c}
    // можно вместо a2 брать b2 или c2 - не принципиально
    vec3D r0_a1(a1, a2);
    vec3D r0_b1(b1, a2);
    vec3D r0_c1(c1, a2);

    rn_a1 = scalar_product(n, r0_a1);
    rn_b1 = scalar_product(n, r0_b1);
    rn_c1 = scalar_product(n, r0_c1);

    // если проекции разных знаков или хотя бы одна 0,
    // есть пересечение, переходим к двумерному случаю в П2
    bool intersect = (rn_a1 * rn_b1 * rn_c1 == 0) ||
                    different_signs(rn_a1, rn_b1, rn_c1);

    if (not intersect) {
        return false;
    } else {
        // проекция треугольника 1 на П2, из которой будем делать
        // многоугольник, являющийся пересечением
        Polygon3D intersect_polygon(
            // здесь "+", конечно, не работает, но для простоты восприятия оставил так
            r0_a1 + rn_a1 + a2,
            r0_b1 + rn_b1 + a2,
            r0_c1 + rn_c1 + a2,
        );

        cut_polygon_by_edge(a2, c2, b2 intersect_polygon);
        if (intersection_polygon.head_vertice() == null_ptr) {
            return false;
        }
        cut_polygon_by_edge(c2, b2, a2, intersect_polygon);
        if (intersection_polygon.head_vertice() == null_ptr) {
            return false;
        }
        cut_polygon_by_edge(b2, c2, a2, intersect_polygon);
        if (intersection_polygon.head_vertice() == null_ptr) {
            return false;
        }
        return true;
    }
}

void cut_polygon_by_edge(const vertice3D& r0,
                         const vertice3D& directing_vertice,
                         const vertice3D& orientation_vertice,
                         Polygon3D& intersect_polygon)
{
    vec3D separating_edge(r0, directing_vertice);
    vec3D orientation_edge(r0, orientation_vertice);
    vec3D orientation_vp = vector_product(separating_edge, orientation_edge);

    vertice3D* head_vertice = intersect_polygon.head_vertice();
    vertice3D* curr_vertice = head_vertice->rlist.next;
    vec3D curr_vec(a2, head_vertice);
    vec3D curr_vp = vector_product(curr_vector, orientation_edge);

    // векторные произведения задают вектор нормали к плоскости, ориентация которого зависит от
    // ориентации входных векторов

    // сравнивая ориентации радиус-вектора заданной точки и base_edge, можно определелить,
    // по разные ли стороны от separating_edge они лежат в П2

    // base_edge задает радиус-вектор от r0 до опорной точки
    float orientation_scalar = scalar_product(curr_vp, orientation_vp);
    if (orientation_scalar < 0) {
        head_vertice.remove_from_list();
    }
    if (curr_vertice == null_ptr) {
        return;
    }
    while (curr_vertice != head_vertice) {
        vec3D curr_vec(r0, curr_vertice);
        vec3D curr_vp = vector_product(curr_vector, orientation_edge);

        float orientation_scalar = scalar_product(curr_vp, orientation_vp);
        if (orientation_scalar < 0) {
            vertice3D* next_vertice = curr_vertice->next;
            curr_vertice.remove_from_list();
            curr_vertice = next_vertice;
        } else {
            curr_vertice = curr_vertice->next;
        }
    }

    // теперь нужно добавить точки пересечения ребер полигона с separation_edge (здесь - прямой)
    // хотелось бы при этом сохранять порядок вершин
    float vertice_to_add = find_intersection(vec3D(head, head->next), separation_edge);
    if (vertice_to_add.is_valid()) {
        head.add(vertice_to_add);
    }
    while (vertice != head) {
        float vertice_to_add = find_intersection(vec3D(vertice, vertice->next), separation_edge);
        if (vertice_to_add.is_valid()) {
            vertice.add(vertice_to_add);
        }
    }
}



```
ISSUES:
- операции с float
- консистентность polygon - чтобы вершины шли по порядку, ну и это не массив, а список, по-хорошему, т.к. сложности с обходом и удалением вершин + консистентностью при этом.
