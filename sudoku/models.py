from django.db import models

class SudokuData(models.Model):
  size = models.IntegerField(default = 0)
  difficulty = models.CharField(max_length = 200, default = '0')
  algorithm = models.CharField(max_length = 200, default = '0')
  time = models.FloatField(default = 0)

  def __str__(self):
    return self.algorithm + ', ' + str(self.size)

  def as_dict(self):
    longDiff = ""
    if(self.difficulty == 'e'):
      longDiff = "easy"
    elif(self.difficulty == 'm'):
      longDiff = "medium"
    elif(self.difficulty == 'h'):
      longDiff = "hard"
    elif(self.difficulty == 'vh'):
      longDiff = "very hard"

    return {
        "id": self.id,
        "size": self.size,
        "difficulty": longDiff,
        "algorithm": self.algorithm,
        "time": self.time,
        }
