var vec=true;
var cy;

function add(str){
	cy.add([
  { group: 'nodes', data: { id: str } }
]);
}

function link(from,to,str){
	cy.add([
  { group: 'edges', data: { id: str, source: from, target: to } ,mode: 'no-cors'}
]);


}

function init(type){
	cy.layout({name: type, randomize: true, animate: true,}).run();
}

function light(str){
	cy.$('#'+str).addClass('highlighted');
}

function remove(str){
	cy.$('#'+str).remove();
}

function offlight(str){
	cy.$('#'+str).removeClass('highlighted');
}

function clear(){
	cy.destroy();
}

function setVec(flag){
	vec=flag;
}

function build(){
	if(vec==true){
		cy = cytoscape({
			container: document.getElementById('cy'),
			boxSelectionEnabled: false,
			autounselectify: true,

			style: cytoscape.stylesheet()
				.selector('node')
				.style({
					'content': 'data(id)'
				})
				.selector('edge')
				.style({
					'curve-style': 'bezier',
					'target-arrow-shape': 'triangle',
					'width': 4,
					'line-color': '#ddd',
					'target-arrow-color': '#ddd'
				})
				.selector('.highlighted')
				.style({
					'background-color': '#61bffc',
					'line-color': '#61bffc',
					'target-arrow-color': '#61bffc',
					'transition-property': 'background-color, line-color, target-arrow-color',
					'transition-duration': '0.2s'
				})
				.selector('.foo')
				.style({
					"label": "data(label)"
				}),
			layout: {
				name: 'grid',
				directed: false,
				roots: '#a',
				padding: 10
			}
		});
	}else{
		cy= cytoscape({
			container: document.getElementById('cy'),
			boxSelectionEnabled: false,
			autounselectify: true,
			style: cytoscape.stylesheet()
				.selector('node')
				.style({
					'content': 'data(id)'
				})
				.selector('edge')
				.style({
					'curve-style': 'bezier',
					'width': 4,
					'line-color': '#ddd',
					'target-arrow-color': '#ddd'
				})
				.selector('.highlighted')
				.style({
					'background-color': '#61bffc',
					'line-color': '#61bffc',
					'target-arrow-color': '#61bffc',
					'transition-property': 'background-color, line-color, target-arrow-color',
					'transition-duration': '0.2s'
				})
				.selector('.foo')
				.style({
					"label": "data(label)"
				}),
			layout: {
				name: 'grid',
				directed: false,
				roots: '#a',
				padding: 10
			}
		});
	}
}
