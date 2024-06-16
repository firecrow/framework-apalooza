declare var window;

export function ExternalConnect(func){
    console.log('refistering function', func);
    window.Fwp.register('vue-app', func);
}