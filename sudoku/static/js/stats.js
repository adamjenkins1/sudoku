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
              x: this.sudokuDataList.rows[i].size,
              y: this.sudokuDataList.rows[i].time
            });
          }
          else if(this.sudokuDataList.rows[i].algorithm == "Genetic") {
            dataPointsGenetic.push({
              x: this.sudokuDataList.rows[i].size,
              y: this.sudokuDataList.rows[i].time
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
                ticks: {
                  min: 4,
                  max: 16,
                },
                type: 'linear',
                position: 'bottom',
                scaleLabel: {
                  display: true,
                  labelString: 'Board Size',
                  fontSize: 15
                }
              }],
              yAxes: [{
                scaleLabel: {
                  display: true,
                  labelString: 'Time (ms)',
                  fontSize: 15
                }
              }]
            },
            title: {
              display: true,
              fontSize: 25,
              text: 'Board Size vs Time'
            },
          }
        });
        //console.log(response);
      }.bind(this));
    }
  }
});

