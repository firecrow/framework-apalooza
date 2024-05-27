
  (function(){
      const appMakeKeys = {
        'react': "FwpReact",
        'vue': "FwpVue",
        'angular': "FwpAngular",
        'svelte': "FwpSvelte",
      };
      const appDict = {};
      const appMakeDict = {};

      function getOrMakeRoot(id){
          let root = document.getElementById(id);
          if(!root){
              root = document.createElement('DIV');
              const allRoot = document.getElementById('app-roots');
              allRoot.appendChild(root);
          }
          return root;
      }

      function hideCurrent(){
          const currentApp = appDict[currentTarget];
          if(currentApp){
              currentApp.hide();
          }
      }

      function addScript(src, callback){
         console.log('making script: ' + src);
         const script = document.createElement('script'); 
         script.setAttribute('src', src);
         script.addEventListener('load', callback);
         document.head.appendChild(script);
      }

      function register(target){
         if(window[appMakeKeys[target]]){
            appMakeDict[target] = window[appMakeKeys[target]];
            LoadApp(target);
         }else{
            throw new Error('Error: unable to find global var ' + appMakeKeys[target] + ' for target ' + target);
         }
      }

      let currentTarget = "";
      function LoadApp(target){
        const app = appDict[target];
        if(app){
          hideCurrent();
          app.show();
          currentTarget = target;
        }else{
          const appMaker = appMakeDict[target];
          if(!appMaker){
              addScript(target + '-app.js', () => register(target));
          }else{
            hideCurrent();
            const id = target+"-root";
            const root = getOrMakeRoot(id);
            appDict[target] = new appMaker.App(root);
            currentTarget = target;
          }
        }
      }

      window.addEventListener("load", function(){
          const li_arr = document.querySelectorAll('nav ul li');
          for(let i = 0; i < li_arr.length; i++){
              (function(appLink){
                const target = appLink.getAttribute('data:target');
                appLink.onclick = () => {
                    LoadApp(target);
                }
              })(li_arr[i]);
          }
      });
  })();
