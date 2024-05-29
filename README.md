# Framework-apalooza

This is a single app build from four frameworks, as a demonstration of each: `React`, `Svelte`, `Angular` and `Vue`, all in one front-end app.

## Project Purpose

The project is inteneded to demonstrate proficiency with `NPM` and `Node.js` build tools as well as the ins-and-outs of various popular frameworks, and show how they can all play nice together when they arrive in the browser. Each app has a different methodology and different development style, but all share common goals and common outcomes. As the project matures I intend to blog extensively about my experience building the same functionality with differnet frameworks.

## Runtime Composition 

The `public` directory contains what will be served to users. With a file for each app named `<name>-app.js` for each framework. These scripts are loaded when the user clicks on the tab for that frameworks app.

## Build System

The build system starts with `build.py` which calls `npm run build` in each framework-app's directory. Each npm pipeline generates JavaScript files in their respective `public` directory. The `build.py` script then pulls them into the outer `public` directory. For example `react-app/public/app.js` becomes `public/react-app.js` and `angular-app/public/polyfill.js` becomes `/public/angular-polyfill.js`.

## Status

The build system(s) for each framework are functioning, with an example application written in each on the way.


## Code Organization

This is the way the apps are laid out in the project.

- build.py: This is the build system written in `Python`
- public: These files are served to users a the browser.
- react-app: Contains the `React` app and `Node.js`, `TypeScript` and `WebPack` build configuration
- svelte-app: Contains the `Svelte` app and `Node.js`,  `TypeScript` and `Vite` based rollup build configuration
- angular-app: Contains the `Svelte` app and `Node.js`,  `TypeScript` and `Angular` build configuration
- vue-app: Contains the `Vue` app and `Node.js`,  `TypeScript` and `Vite` build configuration
