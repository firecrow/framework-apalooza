/*
*  Protractor support is deprecated in Angular.
*  Protractor is used in this example for compatibility with Angular documentation tools.
*/
declare var window:any;

import { bootstrapApplication } from '@angular/platform-browser';
import { AppComponent } from './app/app.component';

export class App  {
    container: HTMLElement;
    constructor(container: HTMLElement){
        this.container = container;

        if(!container.hasChildNodes()){
            const root = document.createElement('fancy-thing');
            container.appendChild(root);
        }

        bootstrapApplication(AppComponent, {providers: []})
          .catch(err => console.error(err));
    }
    hide(){
        this.container.classList.add('hidden');
    }
    show(){
        this.container.classList.remove('hidden');
    }
}

window.FwpAngular = {App: App};
