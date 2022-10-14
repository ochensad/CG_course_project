#include "scene.h"

Scene::Scene(Drawer* canv)
{
    this->canvas = canv;
}

Scene::Scene(int w, int h, int mode)
{
    this->width = w;
    this->height = h;
    this->mode = mode;
}

QImage Scene::draw_scene_1()
{
    QColor cl(255, 4, 33);
    QRgb r = cl.rgb();


    model = new Model();

    QVector3D p1(77.792191, -107.554962, -10.258955);
    QVector3D p2(-136.731628, -107.554947, 5.612476);
    QVector3D p3(-45.351135, 0.010925, -216.835464);
    QVector3D p4(77.792191, 107.555115, -10.258877);
    QVector3D p5(-136.731598, 107.555115, 5.612553);

    model->addSurface(Polygon(p1 , p2 , p3 , r));
    model->addSurface(Polygon(p4 , p2 , p1 , r));
    model->addSurface(Polygon(p1 , p3 , p4 , r));
    model->addSurface(Polygon(p2 , p5 , p3 , r));
    model->addSurface(Polygon(p5 , p4 , p3 , r));
    model->addSurface(Polygon(p5 , p2 , p4 , r));

    QVector3D p1_2(112.397217, -266.872650, -27.462433);
    QVector3D p2_2(64.015358, -334.214539, -23.882843);
    QVector3D p3_2(7.773331, -197.357773, -133.798172);
    QVector3D p4_2(-82.607040, -231.163910, -66.972824);
    QVector3D p5_2(70.398689, -233.336899, 35.783333);
    QVector3D p6_2(-34.225189, -163.822021, -70.552414);
    QVector3D p7_2(22.016830, -300.678772, 39.362923);
    QVector3D p8_2(-40.608505, -264.699646, -130.218582);

    model->addSurface(Polygon(p1_2, p3_2, p2_2, r));
    model->addSurface(Polygon(p4_2, p5_2, p6_2, r));
    model->addSurface(Polygon(p5_2, p4_2, p7_2, r));
    model->addSurface(Polygon(p8_2, p3_2, p2_2, r));
    model->addSurface(Polygon(p5_2, p7_2, p2_2, r));
    model->addSurface(Polygon(p5_2, p3_2, p6_2, r));
    model->addSurface(Polygon(p8_2, p2_2, p7_2, r));
    model->addSurface(Polygon(p6_2, p3_2, p8_2, r));
    model->addSurface(Polygon(p5_2, p1_2, p3_2, r));
    model->addSurface(Polygon(p7_2, p4_2, p8_2, r));
    model->addSurface(Polygon(p2_2, p1_2, p5_2, r));
    model->addSurface(Polygon(p8_2, p4_2, p6_2, r));

    QVector3D p1_3(-138.333954, 171.528900, -11.063049);
    QVector3D p2_3(47.558075, 171.528900, -11.063049);
    QVector3D p3_3(-138.333954, 357.430206, -11.063049);
    QVector3D p4_3(47.558075, 357.430206, -196.955078);
    QVector3D p5_3(-138.333954, 171.528900, -196.955078);
    QVector3D p6_3(-138.333954, 357.430206, -196.955078);
    QVector3D p7_3(47.558075, 171.528900, -196.955078);
    QVector3D p8_3(47.558075, 357.430206, -11.063049);

    model->addSurface(Polygon(p1_3, p3_3, p2_3, r));
    model->addSurface(Polygon(p4_3, p5_3, p6_3, r));
    model->addSurface(Polygon(p5_3, p4_3, p7_3, r));
    model->addSurface(Polygon(p8_3, p3_3, p2_3, r));
    model->addSurface(Polygon(p5_3, p7_3, p2_3, r));
    model->addSurface(Polygon(p5_3, p3_3, p6_3, r));
    model->addSurface(Polygon(p8_3, p2_3, p7_3, r));
    model->addSurface(Polygon(p6_3, p3_3, p8_3, r));
    model->addSurface(Polygon(p5_3, p1_3, p3_3, r));
    model->addSurface(Polygon(p7_3, p4_3, p8_3, r));
    model->addSurface(Polygon(p2_3, p1_3, p5_3, r));
    model->addSurface(Polygon(p8_3, p4_3, p6_3, r));



    QColor lt(255, 255, 255);
    QRgb h = lt.rgb();
    Light l(QVector3D(200, 100, 400), QVector3D(0,0, -600), h, 0.8);
    model->setLight(l);
    if (mode == 0)
        return model->draw(canvas);
    return model->get_image(this->width, this->height);
}

QImage Scene::draw_scene_2()
{
    QColor cl(255, 4, 33);
    QRgb r = cl.rgb();


    model = new Model();

    QVector3D p1(77.754021, -31.003769, 47.128910);
    QVector3D p2(77.754021, -31.003769, -177.120773);
    QVector3D p3(127.162834, 62.073925, -177.120773);
    QVector3D p4(-68.959618, 62.073925, 47.128910);
    QVector3D p5(-68.959618, 62.073925, -177.120773);
    QVector3D p6(-19.550806, -31.003769, -177.120773);
    QVector3D p7(-19.550806, -31.003769, 47.128910);
    QVector3D p8(78.510422, 153.726929, 47.128910);
    QVector3D p9( 78.510422, 153.726929, -177.120773);
    QVector3D p10(127.162834, 62.073925, 47.128910);
    QVector3D p11(-19.550806, 154.201797, -177.120773);
    QVector3D p12(-19.550806, 154.201797, 47.128910);


    model->addSurface(Polygon(p1 , p2 , p3 , r));
    model->addSurface(Polygon(p4 , p5 , p6 , r));
    model->addSurface(Polygon(p4 , p6 , p7 , r));
    model->addSurface(Polygon(p1 , p7 , p2 , r));
    model->addSurface(Polygon(p7 , p6 , p2 , r));
    model->addSurface(Polygon(p7 , p8 , p4 , r));
    model->addSurface(Polygon(p8 , p3 , p9 , r));
    model->addSurface(Polygon(p1 , p3 , p10 , r));
    model->addSurface(Polygon(p6 , p5 , p11 , r));
    model->addSurface(Polygon(p7 , p1 , p10 , r));
    model->addSurface(Polygon(p3 , p6 , p9 , r));
    model->addSurface(Polygon(p4 , p11 , p5 , r));
    model->addSurface(Polygon(p4 , p12 , p11 , r));
    model->addSurface(Polygon(p10 , p8 , p7 , r));
    model->addSurface(Polygon(p8 , p12 , p4 , r));
    model->addSurface(Polygon(p8 , p11 , p12 , r));
    model->addSurface(Polygon(p11 , p9 , p6 , r));
    model->addSurface(Polygon(p8 , p9 , p11 , r));
    model->addSurface(Polygon(p8 , p10 , p3 , r));
    model->addSurface(Polygon(p6 , p3 , p2 , r));

    QVector3D p1_2(14.962830, -183.695923, -15.153243);
    QVector3D p2_2(142.390411, -134.643814, -35.758953);
    QVector3D p3_2(91.490173, -245.837952, -152.576675);
    QVector3D p4_2(66.556686, -310.683441, 1.614013);
    QVector3D p5_2(193.984283, -261.631317, -18.991699);

    model->addSurface(Polygon(p1_2, p2_2, p3_2, r));
    model->addSurface(Polygon(p4_2, p2_2, p1_2, r));
    model->addSurface(Polygon(p1_2, p3_2, p4_2, r));
    model->addSurface(Polygon(p2_2, p5_2, p3_2, r));
    model->addSurface(Polygon(p5_2, p4_2, p3_2, r));
    model->addSurface(Polygon(p5_2, p2_2, p4_2, r));

    QVector3D p1_3(-38.134026, -280.044556, 63.188934);
    QVector3D p2_3(-187.380096, -231.586090, 133.465378);
    QVector3D p3_3(-153.051910, -152.338074, -58.577866);
    QVector3D p4_3(14.962349, -116.514191, 63.188911);
    QVector3D p5_3(-134.283722, -68.055756, 133.465363);

    model->addSurface(Polygon(p1_3, p2_3, p3_3, r));
    model->addSurface(Polygon(p4_3, p2_3, p1_3, r));
    model->addSurface(Polygon(p1_3, p3_3, p4_3, r));
    model->addSurface(Polygon(p2_3, p5_3, p3_3, r));
    model->addSurface(Polygon(p5_3, p4_3, p3_3, r));
    model->addSurface(Polygon(p5_3, p2_3, p4_3, r));



    QColor lt(255, 255, 255);
    QRgb h = lt.rgb();
    Light l(QVector3D(200, 100, 400), QVector3D(0,0, -600), h, 0.8);
    model->setLight(l);
    if (mode == 0)
        return model->draw(canvas);
    return model->get_image(this->width, this->height);
}

QImage Scene::draw_scene_3()
{
    QColor cl(255, 4, 33);
    QRgb r = cl.rgb();


    model = new Model();

    QVector3D p1(-51.302967, -51.305527, 61.158543);
    QVector3D p2(51.302959, -51.305527, 61.158543);
    QVector3D p3(-51.302967, 51.305527, 61.158543);
    QVector3D p4(51.302959, 51.305527, -41.447384);
    QVector3D p5(-51.302967, -51.305527, -41.447384);
    QVector3D p6(-51.302967, 51.305527, -41.447384);
    QVector3D p7(51.302959, -51.305527, -41.447384);
    QVector3D p8(51.302959, 51.305527, 61.158543);


    model->addSurface(Polygon(p1, p3, p2, r));
    model->addSurface(Polygon(p4, p5, p6, r));
    model->addSurface(Polygon(p5, p4, p7, r));
    model->addSurface(Polygon(p8, p3, p2, r));
    model->addSurface(Polygon(p5, p7, p2, r));
    model->addSurface(Polygon(p5, p3, p6, r));
    model->addSurface(Polygon(p8, p2, p7, r));
    model->addSurface(Polygon(p6, p3, p8, r));
    model->addSurface(Polygon(p5, p1, p3, r));
    model->addSurface(Polygon(p7, p4, p8, r));
    model->addSurface(Polygon(p2, p1, p5, r));
    model->addSurface(Polygon(p8, p4, p6, r));

    QVector3D p1_2(-83.066826, -40.447708, -81.050171);
    QVector3D p2_2(-83.082298, -209.406158, 9.855579);
    QVector3D p3_2(83.082336, -124.942657, -35.598591);
    QVector3D p4_2(-27.696638, -198.411011, -172.166016);

    model->addSurface(Polygon(p1_2, p2_2, p3_2, r));
    model->addSurface(Polygon(p1_2, p3_2, p4_2, r));
    model->addSurface(Polygon(p2_2, p4_2, p3_2, r));
    model->addSurface(Polygon(p1_2, p4_2, p2_2, r));


    QVector3D p1_3(-94.409821, -8.216339, -232.373611);
    QVector3D p2_3(94.409637, -8.216339, -232.373611);
    QVector3D p3_3(94.409637, -40.447701, -102.820618);
    QVector3D p4_3(-94.409821, -40.447701, -102.820618);
    QVector3D p5_3(-94.409821, 89.106949, -70.568207);
    QVector3D p6_3(94.409637, 89.106949, -70.568207);

    model->addSurface(Polygon(p1_3, p2_3, p3_3, r));
    model->addSurface(Polygon(p4_3, p5_3, p1_3, r));
    model->addSurface(Polygon(p4_3, p3_3, p6_3, r));
    model->addSurface(Polygon(p5_3, p4_3, p6_3, r));
    model->addSurface(Polygon(p6_3, p2_3, p1_3, r));
    model->addSurface(Polygon(p3_3, p2_3, p6_3, r));
    model->addSurface(Polygon(p3_3, p4_3, p1_3, r));
    model->addSurface(Polygon(p6_3, p1_3, p5_3, r));



    QColor lt(255, 255, 255);
    QRgb h = lt.rgb();
    Light l(QVector3D(200, 100, 400), QVector3D(0,0, -600), h, 0.8);
    model->setLight(l);
    if (mode == 0)
        return model->draw(canvas);
    return model->get_image(this->width, this->height);
}
