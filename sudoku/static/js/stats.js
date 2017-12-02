var count = 0;
var app = new Vue({
  el: '#app',
  data: {
    sudokuDataList: [],
    numRows: Number,
  },
  mounted() {
    this.loadData();

    setInterval(function () {
      this.loadData();
    }.bind(this), 5000);
  },
  methods: {
    loadData: function () {
      $.get('/jsondata', function (response) {
        this.sudokuDataList = response;
        var dataPointsAC3 = [];
        var dataPointsGenetic = [];
        this.numRows = this.sudokuDataList.rows.length;
        for(var i = 0; i < this.sudokuDataList.rows.length; i++) {
          if(this.sudokuDataList.rows[i].algorithm == "AC3") {
            dataPointsAC3.push({
              x: this.sudokuDataList.rows[i].time,
              y: this.sudokuDataList.rows[i].size
            });
          }
          else if(this.sudokuDataList.rows[i].algorithm == "Genetic") {
            dataPointsGenetic.push({
              x: this.sudokuDataList.rows[i].time,
              y: this.sudokuDataList.rows[i].size
            });
          }
        }
        Chart.defaults.global.animation.duration = 0;
        var color = Chart.helpers.color;
        var ctx = document.getElementById("canvas").getContext("2d");
        var scatterChart = new Chart(ctx, {
          type: 'scatter',
          data: {
            datasets: [{
              label: 'AC3',
              borderColor: window.chartColors.red,
              backgroundColor: color(window.chartColors.red).alpha(0.2).rgbString(),
              data: dataPointsAC3
            }, {
              label: 'Genetic',
              borderColor: window.chartColors.blue,
              backgroundColor: color(window.chartColors.blue).alpha(0.2).rgbString(),
              data: dataPointsGenetic
            }]
          },
          options: {
            scales: {
              xAxes: [{
                type: 'linear',
                position: 'bottom',
                scaleLabel: {
                  display: true,
                  labelString: 'Time (ms)',
                  fontSize: 15
                }
              }],
              yAxes: [{
                ticks: {
                  min: 4,
                  max: 16,
                },
                scaleLabel: {
                  display: true,
                  labelString: 'Board Size',
                  fontSize: 15
                }
              }]
            },
            title: {
              display: true,
              fontSize: 25,
              text: 'Time vs Board Size'
            },
          }
        });
        //console.log(response);
      }.bind(this));
    }
  }
});

