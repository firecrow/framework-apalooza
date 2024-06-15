
  (function(){
      const State = {
        keys: {
          'react': "FwpReact",
          'vue': "FwpVue",
          'angular': "FwpAngular",
          'svelte': "FwpSvelte",
        },
        apps: {},
        options: {
            'angular-app.js': {'type': 'module'},
            'angular-polyfill.js': {'type': 'module'}
        },
        preloadScripts: {'angular': ['angular-polyfill.js']},
        scriptsAdded: {},
        makers: {},
        currentKey: "",
      }

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
          if(State.currentKey && State.apps[State.currentKey]){
              State.apps[State.currentKey].hide();
          }
      }

      function addScript(src, callback){
         if(State.scriptsAdded[src]){
              return false;
         }

         const script = document.createElement('script'); 
         script.setAttribute('src', src);
         script.setAttribute('type', 'text/javascript');
         const options = State.options[src];
         for(let key in options){
            script.setAttribute(key, options[key]);
         }
         script.addEventListener('load', callback);
         document.head.appendChild(script);
         State.scriptsAdded[src] = true;
         return true;
      }

      function Register(target){
         const key = State.keys[target];
         if(window[key]){
            State.makers[target] = window[key];
            LoadApp(target);
         }else{
            throw new Error('Error: unable to find global var ' + key + ' for target ' + target);
         }
      }

      function LoadApp(target){
        const app = State.apps[target];
        if(app){
          hideCurrent();
          app.show();
          State.currentKey = target;
        }else{
          const maker = State.makers[target];
          if(!maker){
              console.log(State);
              if(State.preloadScripts[target]){
                  for(let i = 0; i < State.preloadScripts[target].length; i++){
                      const src = State.preloadScripts[target][i];
                      console.log('adding ' + src);
                      if(addScript(src, () => LoadApp(target), State.options[src])){
                          // This return is reached only a new script is added and then the LoadApp functino
                          // will be called again when it's finished loading
                          return ;
                      }
                  }
              }
              const src = target + '-app.js'; 
              addScript(src, () => Register(target));
              // Register will in-turn call LoadApp again when the script loads
          }else{
            hideCurrent();
            const id = target+"-root";
            const root = getOrMakeRoot(id);
            State.apps[target] = new maker.App(root);
            State.currentKey = target;
          }
        }
      }

      class Fwp  {
         constructor(baseUrl){
             this.baseUrl = baseUrl;
             this.listeners =  {};
             this.cached = null;
         }
         makeUrl(path) {
            return `${this.baseUrl}${path}`;
         }
         register(name, func) {
            this.listeners[name] = func; 
            if(this.cached){
                func(this.cached);
            }
         }
         fetch(url) {
            const fullUrl = this.makeUrl(url);
            fetch(fullUrl, {
                method: 'get'
            }).then(resp => {
                if(resp.status === 200){
                    resp.json().then(json => { 
                        for(let k in this.listeners){
                            this.listeners[k](json);
                        }
                        this.cached = json;
                    });
                }else{
                    console.error(`Error fetching '${fullUrl}'`, resp);
                }
            });
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
          const fwp = new Fwp(`${window.location.href}/api/`);
          fwp.register('debug', resp => { console.log('Debug Response', resp) });
          fwp.fetch('start');
          window.Fwp = fwp;
      });
  })();
