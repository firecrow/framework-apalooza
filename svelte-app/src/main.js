import SvelteApp  from './SvelteApp.svelte';

export class App  {
    container;
    constructor(container){
        this.container = container;
        console.log('runnint svelte app');
        const app = new SvelteApp({
            target: container,
            props: {
                name: 'svelte-app'
            }
        });
    }
    hide(){
        this.container.classList.add('hidden');
    }
    show(){
        this.container.classList.remove('hidden');
    }
}