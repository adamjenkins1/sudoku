from django.db import models

class SudokuData(models.Model):
  size = models.IntegerField(default = 0)
  difficulty = models.CharField(max_length = 200, default = '0')
  algorithm = models.CharField(max_length = 200, default = '0')
  time = models.FloatField(default = 0)

  def __str__(self):
    return self.algorithm + ', ' + str(self.size)
