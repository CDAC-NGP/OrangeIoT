
// const apiKey = 'AIzaSyBBIlYm-xe5U0qYxlDXt-UHhQ1YzAdnXZk';
// const videoId = 'zcbPTpwACmo';

const videoId = '1umJpmeOHq4';
const apiKey = 'AIzaSyBBIlYm-xe5U0qYxlDXt-UHhQ1YzAdnXZk'; // Replace with your actual API key
var likesCount;
var targetCount = 4;



    function init() {
        gapi.load('client', function () {
            gapi.client.init({
                apiKey: apiKey,
                discoveryDocs: ['https://www.googleapis.com/discovery/v1/apis/youtube/v3/rest'],
            }).then(function () {
                // Call your function to make YouTube API request here
                getVideoLikes(videoId);
            });
        });
    }

    function getVideoLikes(videoId) {
        gapi.client.youtube.videos.list({
            part: 'snippet,statistics',
            id: videoId,
        }).then(function (response) {
            const likesCount = response.result.items[0].statistics.likeCount;
            console.log(`The video has ${likesCount} likes.`);
            
            // Update the likes count in the HTML
            //document.getElementById('likes').textContent = `Likes: ${likesCount}`;
            useLikesCount(likesCount)
        }, function (error) {
            console.error('Error:', error.result.error.message);
        });
    }

    function useLikesCount(likesCount) {
        if (likesCount >= targetCount){
            const url = 'http://192.168.1.6:5000/actData?id=o101&s1=150&s2=132&do1=1&do2=1';
            fetch(url);

            document.getElementById('likes').textContent = `Likes ${likesCount} :: Target Reached ! Lets Lit Up !!`;
            console.log("Timer is in 1");
            yValues = [likesCount,targetCount];
        }

        if (likesCount < targetCount){
            const url = 'http://192.168.1.6:5000/actData?id=o101&s1=150&s2=132&do1=0&do2=1';
            fetch(url);
            document.getElementById('likes').textContent = `Likes ${likesCount} :: Target Likes ${targetCount}`;
            console.log("Timer is in 0");
            yValues = [likesCount,targetCount];
        }        

    }

    

    function onTimerTick() {
        // Call your function here that you want to run every 2 minutes
        console.log('Timer tick!');
        init(); 
        
          
        
    }

    // Load the client and make API calls
    init();
    setInterval(onTimerTick,6000);

    new Chart("myChart", {
        type: "doughnut",
        data: {
          labels: xValues,
          datasets: [{
            backgroundColor: barColors,
            data: yValues
          }]
        },
        options: {
          title: {
            display: true,
            text: "World Wide Wine Production 2018"
          }
        }
      });
   
     
 



