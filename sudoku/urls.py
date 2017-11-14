from django.conf.urls import url
from django.views.generic.base import RedirectView
from . import views

urlpatterns = [
    url(r'^$', RedirectView.as_view(url = '/9/m/')),
    url(r'^([0-9]+)/([a-z]+)/$', views.index, name = 'index'),
    url(r'^([0-9]+)/([a-z]+)/save/$', views.saveData, name = 'save'),
    url(r'^solve/([A-Za-z0-9]+)/$', views.solve, name = 'solve'),
    url(r'^about/$', views.about, name = 'about'),
    url(r'^stats/$', views.stats, name = 'stats'),
    url(r'^data/$', views.data, name = 'data'),
]
