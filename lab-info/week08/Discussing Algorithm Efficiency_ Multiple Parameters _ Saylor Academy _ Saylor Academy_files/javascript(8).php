
/**
 * Atto HTML editor
 *
 * @package    tool_htmlbootstrapeditor
 * @copyright  2019 RECIT
 * @license    {@link http://www.gnu.org/licenses/gpl-3.0.html} GNU GPL v3 or later
 */
M=M||{};M.recit=M.recit||{};M.recit.htmlbootstrapeditor=M.recit.htmlbootstrapeditor||{};M.recit.htmlbootstrapeditor.settings={currentthemesubrev:1}
M.recit.htmlbootstrapeditor.init_settings=function(_,settings){M.recit.htmlbootstrapeditor.settings=settings}
M.recit.htmlbootstrapeditor.IWrapper={getSettings:null,uploadFile:null,getThemeCssRules:null,getAdditionalHTMLHead:null,getThemeUrl:null,getContent:null,saveContent:null,getTemplateList:null,saveTemplate:null};M.recit.htmlbootstrapeditor.IWrapper.getSettings=function(){var result={};result.wwwroot=M.cfg.wwwroot;result.showcase_url=M.recit.htmlbootstrapeditor.settings.showcase_url;result.iconclass=M.recit.htmlbootstrapeditor.settings.iconclass;result.pixabaykey=M.recit.htmlbootstrapeditor.settings.pixabaykey;return result}
M.recit.htmlbootstrapeditor.IWrapper.getThemeCssRules=function(returnAllRules){var styleSheets=window.document.styleSheets;var cssRulesBuffer={rules:[],urlList:[]};var titles=M.recit.htmlbootstrapeditor.settings.stylesheet_to_add
if(titles){titles=titles.split(',')}else{titles=[]}
for(var sheet of styleSheets){if((sheet.href&&sheet.href.includes(`/theme/styles.php/${M.cfg.theme}`))||(titles.includes(sheet.title)||titles.includes(sheet.href))){if(sheet.href==null||returnAllRules){for(var rule of sheet.rules){cssRulesBuffer.rules.push(rule)}}
if(sheet.href){cssRulesBuffer.urlList.push(sheet.href)}}}
return cssRulesBuffer}
M.recit.htmlbootstrapeditor.IWrapper.getAdditionalHTMLHead=function(){let result={css:[],js:[]};if(M.recit.htmlbootstrapeditor.settings.additionalstylesheet.length>0){result.css=M.recit.htmlbootstrapeditor.settings.additionalstylesheet.split('\n')}
return result}
M.recit.htmlbootstrapeditor.IWrapper.saveTemplate=function(data){return M.recit.htmlbootstrapeditor.queryMoodle('htmlbootstrapeditor_save_template',data)}
M.recit.htmlbootstrapeditor.IWrapper.getTemplateList=function(type){return M.recit.htmlbootstrapeditor.queryMoodle('htmlbootstrapeditor_get_template_list',{type:type})}
M.recit.htmlbootstrapeditor.IWrapper.deleteTemplate=function(id){return M.recit.htmlbootstrapeditor.queryMoodle('htmlbootstrapeditor_delete_template',{id:id})}
M.recit.htmlbootstrapeditor.IWrapper.importTemplates=function(fileContent){return M.recit.htmlbootstrapeditor.queryMoodle('htmlbootstrapeditor_import_templates',{fileContent:fileContent})}
M.recit.htmlbootstrapeditor.post=function(url,data){let result=new Promise((resolve,reject)=>{data=JSON.stringify(data);let xhr=new XMLHttpRequest();xhr.open("post",url,!0);xhr.setRequestHeader('Content-Type','application/json; charset=utf-8');xhr.setRequestHeader('Accept','json');xhr.onload=function(event){let response=null;try{response=JSON.parse(event.target.response)}catch(error){reject(error,event.target.response)}
resolve(response)}
xhr.onerror=function(err){reject(err)}
xhr.send(data)});return result}
M.recit.htmlbootstrapeditor.queryMoodle=function(methodName,args,onSuccess){let data={index:0,args:args,methodname:methodName};return M.recit.htmlbootstrapeditor.post(M.cfg.wwwroot+"/lib/ajax/service.php?sesskey="+M.cfg.sesskey+"&info="+methodName,[data],onSuccess)}