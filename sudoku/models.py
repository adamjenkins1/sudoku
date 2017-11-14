from django.db import models

class SudokuData(models.Model):
  size = models.IntegerField(default = 0)
  difficulty = models.CharField(max_length = 200)
  ac3Time = models.FloatField(null = True)
  geneTime = models.FloatField(null = True)
