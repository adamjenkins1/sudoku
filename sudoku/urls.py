from django.conf.urls import url
from django.views.generic.base import RedirectView
from . import views

urlpatterns = [
    url(r'^$', RedirectView.as_view(url = '/9/m/')),
    url(r'^([0-9]+)/([a-z]+)/$', views.index, name = 'index'),
    url(r'^about/$', views.about, name = 'about'),
]
