
  (function(){
      const appMakeDict = {
        'react': "FwpReact" in window && FwpReact,
        'vue': "FwpVue" in window && FwpVue,
        'angular': "FwpAngular" in window && FwpAngular,
        'svelte': "FwpSvelte" in window && FwpSvelte,
      };
      const appDict = {};

      function getOrMakeRoot(id){
          let root = document.getElementById(id);
          if(!root){
              root = document.createElement('DIV');
              const allRoot = document.getElementById('app-roots');
              allRoot.appendChild(root);
          }
          return root;
      }

      let currentTarget = "";
      function LoadApp(target){
        const currentApp = appDict[currentTarget];
        if(currentApp){
          currentApp.hide();
        }
        const app = appDict[target];
        if(app){
          app.show();
        }else{
          const appMaker = appMakeDict[target];
          if(appMaker){
            const id = target+"-root";
            const root = getOrMakeRoot(id);
            appDict[target] = new appMaker.App(root);
          }else{
            console.warn("App Maker not found for: " + target);
          }
        }
        currentTarget = target;
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
